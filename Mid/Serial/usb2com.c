/*
 *  usb2com.c
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#include "usb2com.h"
#include "uart.h"
#include "stm32f10x_usart.h"
#include "xor.h"
#include "queue.h"
#include "appusb2com_main.h"

QUEUEx_t usb2comCommandQueue;
u8 usb2comCommandBuff[USB2COM_COMMAND_MAX_SIZE];

/******************************************************************************/
/*                              FUNCTION                                      */
/******************************************************************************/

/*!
 * @brief functions USB2COM_Init.
 *
 */
void USB2COM_Init(void)
{
    UART_Init(USB2COM_COM, USB2COM_BAUDRATE, USART_Mode_Tx|USART_Mode_Rx);
    UART_CallBackInit(USB2COM_COM, USB2COM_CallBackHandle);
    QUEUE_Init(&usb2comCommandQueue, (u8*)usb2comCommandBuff,\
                USB2COM_COMMAND_MAX_SIZE, sizeof(USB2COM_Command_t));
    USART_Cmd(USB2COM_COM, ENABLE);
}

/*!
 * @brief functions UART_CallBackHandle.
 *
 */
void USB2COM_CallBackHandle(USART_TypeDef* USARTx)
{
    static u8 revByteCount = 0;
    static u8 revBuff[USB2COM_COMMAND_HEADER_SIZE + USB2COM_COMMAND_MAX_LENGH + 1];
    u8 revByte = 0;
    
    revByte = UART_GetData(USARTx);
    revBuff[revByteCount++] = revByte;
    if(revByteCount >= USB2COM_COMMAND_HEADER_SIZE)
    {
        if(revByteCount == USB2COM_COMMAND_HEADER_SIZE + revBuff[3] + 1)
        {
            if(revBuff[USB2COM_COMMAND_HEADER_SIZE + revBuff[3]] ==\
                XOR_Caculator(revBuff, 0, USB2COM_COMMAND_HEADER_SIZE + revBuff[3]))
            {
                QUEUE_Push(&usb2comCommandQueue, revBuff);
            }
            revByteCount = 0;
        }
    }
}

/*!
 * @brief functions USB2COM_Proc.
 *
 */
void USB2COM_Proc(void)
{
    USB2COM_Command_t usb2com_command;
    if(!QUEUE_Empty(&usb2comCommandQueue))
    {
        QUEUE_Get(&usb2comCommandQueue, (u8*)&usb2com_command);
        BLE_CheckCommandExitsAndExecute(usb2com_command.command, \
            usb2com_command.type, usb2com_command.buff, usb2com_command.length);
    }

}

/*!
 * @brief functions USB2COM_Send.
 *
 */
void USB2COM_Send(u8* buff, u8 length)
{
    UART_SendData(USB2COM_COM, buff, length);
}