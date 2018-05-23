#include "state_machine.h"

uint8_t ui8_State = 0, ui8_PreMode;
float f_Velocity;
int32_t i32_PrePosition=0;
extern int8_t txbuff[] ;
void v_ImplementStateMachine( void )
{
    if(ui8_PreMode!=i8_GetMode())
    {
        v_ClearPre();
        i32_PrePosition=i32_GetPosition();
    }
    if(i8_GetMode())// position so 1
    {
        v_SetPulseRate(f32_PID_PIDProcess(f_GetSetPoint(),i32_GetPosition()));
        sprintf(txbuff,"%d\n",i32_GetPosition());
    }
    else // van toc so 0
    {   
        f_Velocity=(float)((i32_GetPosition()-i32_PrePosition)/0.1);
        v_SetPulseRate(f32_PID_PIDProcess(f_GetSetPoint(),f_Velocity));
        sprintf(txbuff,"%f\n",f_Velocity);
    }
    DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
    DMA1_Stream4->NDTR = strlen(txbuff);
    DMA_Cmd(DMA1_Stream4, ENABLE);
    v_Convert();
    ui8_PreMode = i8_GetMode();
    i32_PrePosition=i32_GetPosition();
    v_ResetStateStatus(0);

}


uint8_t ui8_GetStateStatus ( void )
{
    return ui8_State;
}


void v_SetStateStatus ( uint8_t ui8_newstatus )
{
    ui8_State |= ui8_newstatus;
}

void v_ResetStateStatus ( uint8_t ui8_newstatus )
{
    ui8_State = ui8_newstatus;
}