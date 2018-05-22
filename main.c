#include "main.h"
volatile int32_t debug;
int main(void)
{
	int32_t i;
	//v_InitTimerBase();
	//v_PWM_Config();
	v_InitEncoder();
	//v_Uart_InitUart(9600);
	//v_SetPulseRate(23.6);
	//v_Debug_InitLedDebug();
	while(1){
		/* code */
		debug=i32_GetPosition();
	}
	return 0;
}







