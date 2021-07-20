/*
 * ProtocolData.h
 *
 *  Created on: Sep 7, 2017
 *      Author: guoxs
 */

#ifndef _UART_PROTOCOL_DATA_H_
#define _UART_PROTOCOL_DATA_H_

#include <string>
#include "CommDef.h"

/******************** CmdID ***********************/
#define CMDID_PAPER_EXCEED                  0x01
#define CMDID_SHORTAGE                      0x02
#define CMDID_PAPER_NUM                     0x03
#define CMDID_CALIBRATION                   0x04
#define CMDID_MEASURE                       0x05
#define CMDID_SELF_CHECK                    0x06
#define CMDID_CALIBRATE_                    0x07//接收的命令形式
#define cmdID_CALIBRATE_NUM                 '7'//校准时发送的命令形式
#define cmdID_SELF_CHECK                    '6'
#define cmdID_MEASURE                       '5'
#define CMDID_DEBUG                         0xEB90
/**************************************************/

/******************** 错误码 Error code ***********************/
#define ERROR_CODE_CMDID			1
/**************************************************/

typedef enum feedbackType {
	calibration,
	shortageError,
	paperResult,
	debugResult
} feedbackType;

typedef struct {
	feedbackType type;
	BYTE paper_num;
	BYTE shortage;
	BYTE paper_exceed;
	BYTE calibration;
	BYTE debug_data[400];
} SProtocolData;

#endif /* _UART_PROTOCOL_DATA_H_ */
