#ifndef __UART_H
#define __UART_H

#include "main.h"

/**/
/*typedef struct
{
    int8_t so[17];
    int8_t so1;
    int8_t so2;
    int8_t so3;
    int8_t so4;
    int8_t so5;
    int8_t so6;
    int8_t so7;
    int8_t so8;
    int8_t so9;
    int8_t so10;
    int8_t so11;
    int8_t so12;
    int8_t so13;
    int8_t so14;
    int8_t so15;
    int8_t so16;
} IntStruct;*/

typedef struct 
{
    int8_t Mode;
    float SetPoint;
    float KpValue;
		float KdValue;
    float KiValue;
} buffer_type;

union float_convert
{
    /*IntStruct Int8Value;*/
		int8_t so[19];
    buffer_type stru_Buffer;
};


/**/

void v_Uart_InitUart(int16_t baudrate);
void v_ReadRxBuffer(int8_t* i8_RxData);
void v_SendTxBuffer(int8_t* i8_TxData);
void v_Convert(void);
float f_GetSetPoint( void );
int8_t i8_GetMode( void );	

#endif // __UART_H
