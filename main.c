#include "main.h"
volatile int32_t debug;
int main(void)
{
	//int32_t i;
	//v_InitTimerBase();
	v_PWM_Config();
	v_InitEncoder();
	//v_Uart_InitUart(9600);
	//v_SetPulseRate(23.6);
	//v_Debug_InitLedDebug();
	v_GPIO_GPIOInit();
	GPIO_ResetBits(GPIOD,GPIO_Pin_11);
	//GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	while(1){
		/* code */
		debug=i32_GetPosition();
	//GPIO_SetBits(GPIOD,GPIO_Pin_11);
	//(GPIOC,GPIO_Pin_6);
	}
	return 0;
}







