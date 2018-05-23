#include "PID.h"

float PID_PGain= 0.001,PID_IGain = 0,PID_DGain = 0,f32_Error;
float f32_PreError=0,f32_PreIvalue=0;
float f32_PID_PIDProcess( float f32_SetPoint, float f32_Value)
{
    float f32_IValue,f32_DValue,f32_Result;
    f32_Error  = f32_SetPoint - f32_Value;
    f32_IValue = f32_PreIvalue + (f32_Error + f32_PreError) * DT_S / 2;
    f32_DValue = (f32_Error - f32_PreError) / DT_S;
    f32_Result = PID_PGain*f32_Error + PID_IGain*f32_IValue + PID_DGain*f32_DValue;
    f32_PreError = f32_Error;
    f32_PreIvalue = f32_IValue;
    if (f32_Result < -100)
    {
        f32_Result = -100;
    }
    if (f32_Result > 100)
    {
        f32_Result = 100;
    }
    return f32_Result;
}
    
void v_ClearPre(void)
{
    f32_PreError=0;
    f32_PreIvalue=0;
}

void v_SetPGain( float f32_Value )
{
    PID_PGain = f32_Value;
}

void v_SetIGain( float f32_Value )
{
    PID_IGain = f32_Value;
}

void v_SetDGain( float f32_Value )
{
    PID_DGain = f32_Value;
}

float f32_GetPGain (void)
{
    return PID_PGain;
}

float f32_GetIGain (void)
{
    return PID_IGain;
}

float f32_GetDGain (void)
{
    return PID_DGain;
}

float f32_GetError (void)
{
    return f32_Error;
}