#include "uart.h"

#define		BUFF_SIZE_TX		6
#define		BUFF_SIZE_RX		17
uint8_t     txbuff[] = {'a',2,3,4,5,6};
uint8_t 	rxbuff[17];
uint8_t* test2;
float* test;
union float_convert uni_RxBuff,abc;

void v_Uart_InitUart(int16_t baudrate)
{
    // /* use uart2 PA2:TX PA3:RX */
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
    // RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );

    // /*config io pin*/
    // GPIO_InitTypeDef x_GPIOInit;
    // x_GPIOInit.GPIO_Mode = GPIO_Mode_AF;
    // x_GPIOInit.GPIO_OType = GPIO_OType_PP;
    // x_GPIOInit.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
    // x_GPIOInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
    // GPIO_Init(GPIOA, &x_GPIOInit);
  
    // GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
    // GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);

    GPIO_InitTypeDef 	GPIO_InitStructure; 
    USART_InitTypeDef USART_InitStructure;   
    DMA_InitTypeDef  	DMA_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;	

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    /* Enable DMA1 clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

    /* Connect UART4 pins to AF2 */  
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4); 

    /* GPIO Configuration for UART4 Tx */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIO Configuration for USART Rx */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
        
    /* USARTx configured as follow:
        - BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(UART4, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(UART4, ENABLE);

    /* Enable UART4 DMA */
    USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE); 


    /* DMA1 Stream4 Channel4 for UART4 Tx configuration */			
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)txbuff;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_BufferSize = BUFF_SIZE_TX;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream4, &DMA_InitStructure);
    DMA_Cmd(DMA1_Stream4, ENABLE);
    
    /* Enable UART4 DMA */
    USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
        
    /* DMA1 Stream2 Channel4 for USART4 Rx configuration */			
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rxbuff;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = BUFF_SIZE_RX;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream2, &DMA_InitStructure);
    DMA_Cmd(DMA1_Stream2, ENABLE);

    /* Enable DMA Interrupt to the highest priority */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Transfer complete interrupt mask */
    DMA_ITConfig(DMA1_Stream2, DMA_IT_TC, ENABLE);

} 
void v_ReadRxBuffer(int8_t* i8_RxData)
{
		int8_t cnt=0;
    for(cnt = 0; cnt < BUFF_SIZE_RX; cnt++)
    {
        /* code */
        i8_RxData[cnt] = rxbuff[cnt];
    }
}

void v_SendTxBuffer(int8_t* i8_TxData)
{
    int8_t cnt=0;
    
    for(cnt = 0; cnt < BUFF_SIZE_TX; cnt++)
    {
        /* code */
        txbuff[cnt] = i8_TxData[cnt];
    }
}


void DMA1_Stream2_IRQHandler(void)
{
    /* Clear the DMA1_Stream2 TCIF2 pending bit */
    DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);
    DMA_Cmd(DMA1_Stream2, ENABLE);
}

void v_Convert(void)
{
	uni_RxBuff.so[0] = rxbuff[0];
	for(int cnt =0; cnt<16;cnt++)
	{
		uni_RxBuff.so[cnt+4] = rxbuff[cnt+1];
	}
	v_SetPGain(uni_RxBuff.stru_Buffer.KpValue);
	v_SetIGain(uni_RxBuff.stru_Buffer.KiValue);
	v_SetDGain(uni_RxBuff.stru_Buffer.KdValue);
}

float f_GetSetPoint( void )
{
		return uni_RxBuff.stru_Buffer.SetPoint;
}

int8_t i8_GetMode( void )
{
		return uni_RxBuff.stru_Buffer.Mode;
}