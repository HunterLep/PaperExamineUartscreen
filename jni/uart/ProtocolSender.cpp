/*
 * ProtocolSender.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: guoxs
 */

#include "uart/ProtocolSender.h"
#include "uart/UartContext.h"
#include "utils/Log.h"
#include <stdio.h>
#include "string.h"

extern BYTE getCheckSum(const BYTE *pData, int len);

/**
 * 需要根据协议格式进行拼接，以下只是个模板
 * Need to be spliced ​​according to the agreement format, the following is just a template
 */
bool sendProtocol(const BYTE cmdID, const BYTE *pData, BYTE len) {
	if (len + DATA_PACKAGE_MIN_LEN > 256) {
		LOGE("sendProtocol data is too len !!!\n");
		return false;
	}

	BYTE dataBuf[256];

	/*
	dataBuf[0] = CMD_HEAD1;
	dataBuf[1] = CMD_HEAD2;			// 同步帧头 Sync frame header

	dataBuf[2] = HIBYTE(cmdID);
	dataBuf[3] = LOBYTE(cmdID);		// 命令字节 Command byte

	dataBuf[4] = len;

	UINT frameLen = 5;

	// 数据 Data
	for (int i = 0; i < len; ++i) {
		dataBuf[frameLen] = pData[i];
		frameLen++;
	}
#ifdef PRO_SUPPORT_CHECK_SUM
	// 校验码 Checksum
	dataBuf[frameLen] = getCheckSum(dataBuf, frameLen);
	frameLen++;
#endif

	return UARTCONTEXT->send(dataBuf, frameLen);
	*/
	dataBuf[0]=cmdID;

	UINT framelen=1;

	for(int i=0;i<len;++i){
		dataBuf[framelen]=pData[i];
		framelen++;
	}
	dataBuf[framelen]='\0';
	framelen++;
#ifdef PRO_SUPPORT_CHECK_SUM
	//校验码 Checksum
	dataBuf[framelen]=getCheckSum(dataBuf,framelen);
	framelen++;
#endif

	return UARTCONTEXT->send(dataBuf,framelen);
}

bool sendnumProtocol(const BYTE cmdID,UINT* num,UINT len){
	char dataBuf[256];
	if(cmdID=='7'){
		sprintf(dataBuf,"7C%c",num[0]);
	return UARTCONTEXT->sendnum(dataBuf, len);
	}
}
