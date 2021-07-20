/*
 * ProtocolParser.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: guoxs
 */
#include <vector>
#include <string.h>
#include <system/Mutex.h>
#include "CommDef.h"
#include "uart/ProtocolParser.h"
#include "utils/Log.h"

static Mutex sLock;
static std::vector<OnProtocolDataUpdateFun> sProtocolDataUpdateListenerList;

void registerProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener) {
	Mutex::Autolock _l(sLock);
	LOGD("registerProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		sProtocolDataUpdateListenerList.push_back(pListener);
	}
}

void unregisterProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener) {
	Mutex::Autolock _l(sLock);
	LOGD("unregisterProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		std::vector<OnProtocolDataUpdateFun>::iterator iter = sProtocolDataUpdateListenerList.begin();
		for (; iter != sProtocolDataUpdateListenerList.end(); iter++) {
			if ((*iter) == pListener) {
				sProtocolDataUpdateListenerList.erase(iter);
				return;
			}
		}
	}
}

static void notifyProtocolDataUpdate(const SProtocolData &data) {
	Mutex::Autolock _l(sLock);
	std::vector<OnProtocolDataUpdateFun>::const_iterator iter = sProtocolDataUpdateListenerList.begin();
	for (; iter != sProtocolDataUpdateListenerList.end(); iter++) {
		(*iter)(data);
	}
}

static SProtocolData sProtocolData;

SProtocolData& getProtocolData() {
	return sProtocolData;
}

/**
 * 获取校验码
 * Get checksum code
 */
BYTE getCheckSum(const BYTE *pData, int len) {
	int sum = 0;
	for (int i = 0; i < len; ++i) {
		sum += pData[i];
	}

	return (BYTE) (~sum + 1);
}

/**
 * 解析每一帧数据
 * Parse each frame of data
 */
static void procParse(const BYTE *pData, UINT len) {
	// CmdID
	switch (MAKEWORD(pData[3], pData[2])) {
	case CMDID_PAPER_EXCEED:
		sProtocolData.type = paperResult;
		if(pData[5]==0x01){
			sProtocolData.paper_exceed = pData[5];
		}
		else{
			sProtocolData.paper_exceed = 0x00;
		}
		break;
	case CMDID_PAPER_NUM:
		sProtocolData.type = paperResult;
		sProtocolData.paper_num = pData[5];
		break;
	case CMDID_SHORTAGE:
		sProtocolData.type = shortageError;
		sProtocolData.shortage = pData[5];
		break;
	case CMDID_CALIBRATION:
		sProtocolData.type = calibration;
		sProtocolData.calibration = pData[5];
		break;
	case CMDID_DEBUG:
		sProtocolData.type = debugResult;
		for(int i=0;i<pData[4];i++){
			sProtocolData.debug_data[i] = pData[i+5];
		}
		sProtocolData.debug_data[pData[4]] = '\0';
		//LOGD("\n%x", sProtocolData.debug_data[pData[4] - 1]);
	}

	// 通知协议数据更新
  // Notify protocol data update
	notifyProtocolDataUpdate(sProtocolData);
}

/**
 * 功能：解析协议 
 * Function: Parse protocol
 * 参数：pData 协议数据，len 数据长度
 * Parameters: pData - protocol data, len - data length
 * 返回值：实际解析协议的长度
 * Return value: the length of the actual resolution protocol
 */
int parseProtocol(const BYTE *pData, UINT len) {
	UINT remainLen = len;	// 剩余数据长度 Remaining data length
	UINT dataLen;	// 数据包长度 Packet length
 	UINT frameLen;	// 帧长度 Frame length
 	//LOGD("%x %x \n", pData[0], pData[1]);
 	//LOGD("%d\n", remainLen);
	/**
	 * 以下部分需要根据协议格式进行相应的修改，解析出每一帧的数据
   * The following parts need to be modified according to the protocol format to parse out the data of each frame
	 */
 	if(len<DATA_PACKAGE_MIN_LEN){
 		return 0;
 	}

	while (remainLen >= DATA_PACKAGE_MIN_LEN) {
		// 找到一帧数据的数据头
    // Find the data header of a frame of data
		while ((remainLen >= 2) && ((pData[0] != CMD_HEAD1) || (pData[1] != CMD_HEAD2))) {
			pData++;
			remainLen--;
			continue;
		}

		if (remainLen < DATA_PACKAGE_MIN_LEN) {
			//LOGD("%d 1\n", remainLen);
			break;
		}

		dataLen = pData[4];
		frameLen = dataLen + DATA_PACKAGE_MIN_LEN;
		if (frameLen > remainLen) {
			// 数据内容不全
      // Incomplete data packet
			//LOGD("%d %d 2\n", dataLen, frameLen);
			break;
		}
		for (UINT i = 0; i < frameLen; ++i) {
			//LOGD("%x ", pData[i]);
		}
		//LOGD("\n");
		// 打印一帧数据，需要时在CommDef.h文件中打开DEBUG_PRO_DATA宏
    // To print a data of frame, open the DEBUG_PRO_DATA macro in the CommDef.h file when needed
#ifdef DEBUG_PRO_DATA
		for (UINT i = 0; i < frameLen; ++i) {
			LOGD("%x ", pData[i]);
		}
		LOGD("\n");
#endif

		// 支持checksum校验，需要时在CommDef.h文件中打开PRO_SUPPORT_CHECK_SUM宏
    // Support checksum verification, open the PRO_SUPPORT_CHECK_SUM macro in CommDef.h file when needed
#ifdef PRO_SUPPORT_CHECK_SUM
		// 检测校验码 Checksum
		if (getCheckSum(pData, frameLen - 1) == pData[frameLen - 1]) {
			// 解析一帧数据
      // Parse a data of frame
			procParse(pData, frameLen);
		} else {
			LOGE("CheckSum error!!!!!!\n");
		}
#else
		// 解析一帧数据
    // Parse a data of frame
		procParse(pData, frameLen);
#endif

		pData += frameLen;
		remainLen -= frameLen;
	}

	return len - remainLen;
}
