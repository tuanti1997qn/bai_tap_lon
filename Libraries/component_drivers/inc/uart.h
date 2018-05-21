#ifndef __UART_H
#define __UART_H

#include "main.h"


void v_Uart_InitUart(int16_t baudrate);
void v_ReadRxBuffer(int8_t* i8_RxData);
void v_SendTxBuffer(int8_t* i8_TxData);

#endif // __UART_H
