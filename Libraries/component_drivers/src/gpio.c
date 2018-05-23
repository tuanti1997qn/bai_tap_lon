#include "gpio.h"

void v_GPIO_GPIOInit( void )
{
   /* RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC , ENABLE);
    GPIO_InitTypeDef stru_InitGPIO;
    stru_InitGPIO.GPIO_Mode = GPIO_Mode_OUT;
    stru_InitGPIO.GPIO_OType = GPIO_OType_OD;
    stru_InitGPIO.GPIO_Pin = GPIO_Pin_6;
    stru_InitGPIO.GPIO_PuPd = GPIO_PuPd_UP;
    stru_InitGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &stru_InitGPIO);*/

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD	, ENABLE);
		GPIO_InitTypeDef stru_InitGPIO;
    stru_InitGPIO.GPIO_Mode = GPIO_Mode_OUT;
    stru_InitGPIO.GPIO_OType = GPIO_OType_OD;
    stru_InitGPIO.GPIO_Pin = GPIO_Pin_11;
    stru_InitGPIO.GPIO_PuPd = GPIO_PuPd_UP;
    stru_InitGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &stru_InitGPIO);
}