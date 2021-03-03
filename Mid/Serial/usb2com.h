/*
 *  usb2com.h
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#ifndef _USB2COM_H_
#define _USB2COM_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "stm32f10x.h"

/******************************************************************************/
/*                              DEFINE                                        */
/******************************************************************************/

#define USB2COM_COM               USART3
#define USB2COM_BAUDRATE          115200


void USB2COM_Init(void);
void USB2COM_CallBackHandle(USART_TypeDef* USARTx);
void USB2COM_Proc(void);
void USB2COM_Send(u8* buff, u8 length);

#endif /*_USB2COM_H_*/