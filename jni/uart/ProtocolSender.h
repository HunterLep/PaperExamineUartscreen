/*
 * ProtocolSender.h
 *
 *  Created on: Sep 8, 2017
 *      Author: guoxs
 */

#ifndef _UART_PROTOCOL_SENDER_H_
#define _UART_PROTOCOL_SENDER_H_

#include "CommDef.h"

bool sendProtocol(const BYTE cmdID,const BYTE *pData, BYTE len);
bool sendnumProtocol(const BYTE cmdID,UINT* num,UINT len);

#endif /* _UART_PROTOCOL_SENDER_H_ */
