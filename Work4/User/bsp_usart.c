# include "stm32f10x_usart.h"
# include "bsp_usart.h"
# include "stm32f10x.h"
# include "string.h"

/*
    Here is the file for USART configuration and initialization and transmission.
*/

void USART_Config(void)
{
    //Define the USART1 configuration structure
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    //Enable the clock for USART1 and GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);

    //Configure the USART1 pins (TX PA.9)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    //Configure the USART1 pins (RX PA.10)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure the USART1
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

void Usart_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
    // send a byte to USART
    USART_SendData(pUSARTx, ch);
    // wait until the data is sent
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void Usart_SendString(USART_TypeDef * pUSARTx, char *str)
{
    // send a string to USART
    while (*str != '\0')
    {
        Usart_SendByte(pUSARTx, *str++);
    }
}

void Usart_SendStringDMA(USART_TypeDef *pUSARTx, const char *str)
{
    // send a string to USART using DMA
    DMA_InitTypeDef DMA_InitStructure;

    // configure DMA
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    // USART1_TX DMA1_Channel4
    DMA_DeInit(DMA1_Channel4); 

    // set DMA transfer parameters
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&pUSARTx->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)str;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = strlen(str);
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);

    // Open USART DMA TX
    USART_DMACmd(pUSARTx, USART_DMAReq_Tx, ENABLE);

    // enable DMA
    DMA_Cmd(DMA1_Channel4, ENABLE);
}
