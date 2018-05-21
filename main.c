#include "main.h"

int main(void)
{
	//v_InitTimerBase();
	v_PWM_Config();
	//v_InitEncoder();
	//v_Uart_InitUart(9600);
	v_SetPulseRate(23.6);
	while(1){
		/* code */
	}
	return 0;
}







