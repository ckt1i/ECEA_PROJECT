# include "beep.h"
#include "stm32f10x.h" 
#include "stm32f10x_conf.h" 

/*
    Here is the function to control the beeper.
*/

// set the status of the beep
void BEEP(uint8_t status)
{
    if(status == BEEP_ON)
    {
        GPIO_SetBits(GPIOA, BEEP_PIN);
    }
    else
    {
        GPIO_ResetBits(GPIOA, BEEP_PIN);
    }
}

void BEEP_Init(void)
{
    //instantialize setting the GPIO pin and mode
    GPIO_InitTypeDef GPIO_InitStructure;

    // enable the clock of GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // set the GPIO pin and mode and speed
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // initialize the GPIO
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // turn off the beep after initialization
    BEEP(BEEP_OFF);
}

