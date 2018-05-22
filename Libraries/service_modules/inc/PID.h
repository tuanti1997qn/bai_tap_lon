#ifndef __PID_H
#define __PID_H

#include "main.h"

// dt = 0.1s depend on timer.h
#define DT_S 0.1

float f32_PID_PIDProcess( float f32_SetPoint, float f32_Value);
void v_SetPGain( float f32_Value );
void v_SetIGain( float f32_Value );
void v_SetDGain( float f32_Value );
float f32_GetPGain (void);
float f32_GetIGain (void);
float f32_GetDGain (void);

#endif