/*
 *  bluetooth.h
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "stm32f10x.h"

/******************************************************************************/
/*                              DEFINE                                        */
/******************************************************************************/

#define BLUETOOTH_COM               USART1
#define BLUETOOTH_BAUDRATE          115200


void BLUETOOTH_Init(void);
void BLUETOOTH_CallBackHandle(USART_TypeDef* USARTx);
void BLUETOOTH_Proc(void);
void BLUETOOTH_Send(u8* buff, u8 length);

#endif /*_BLUETOOTH_H_*/