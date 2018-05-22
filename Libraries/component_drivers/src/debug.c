#include "debug.h"

void v_Debug_InitLedDebug( void )
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef x_GpioInit;
    x_GpioInit.GPIO_Mode = GPIO_Mode_OUT; 
    x_GpioInit.GPIO_OType = GPIO_OType_PP;
    x_GpioInit.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    x_GpioInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
    x_GpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &x_GpioInit);
}

void v_Debug_Toggle_led(LedNum x_led)
{
    GPIO_ToggleBits(GPIOD , x_led);
}