#ifndef __PWM_H
#define __PWM_H

#include "main.h"

#define TIM_PERIOD (4200 -1)
#define PRESCALER_VAL 0
#define DEFAULT_PULSE (2100 -1)

void v_PWM_Config(void);
void v_SetPulse( uint16_t ui16_Pulse );
void v_SetPulseRate( float f_Rate);

#endif