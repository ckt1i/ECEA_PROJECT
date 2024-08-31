#include "stm32f10x.h"
#include "bsp_led_colors.h"

/*
    This program is used to control the color LED. And make it flash 7 colors in turn of 1 second.
*/

// the main function
int main(void)
{
    // make the initialization
    NVIC_InitTypeDef NVIC_InitStructure;

    // Initialize the Color LED and make it flash 7 colors in turn of 1 second
    COLOR_TIMx_GPIO_Config();
    COLOR_PWM_Config();
    COLOR_TIMx4_Config();

    // Configure TIM4 interrupt
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    while (1)
    {
        // Main loop does nothing, waiting for interrupts
    }
}
