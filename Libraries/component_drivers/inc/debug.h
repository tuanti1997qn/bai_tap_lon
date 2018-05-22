#ifndef __DEBUG_H
#define __DEBUG_H

#include "main.h"

typedef enum{
    Led_1 = GPIO_Pin_12,
    Led_2 = GPIO_Pin_13,
    Led_3 = GPIO_Pin_14,
    Led_4 = GPIO_Pin_15,
} LedNum;

void v_Debug_InitLedDebug( void );
void v_Debug_Toggle_led(LedNum x_led);

#endif