#include "bsp_led_colors.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h" 
#include "stm32f10x_tim.h"

/*
    Here I update the files in the folder to make the LED can show 7 colors in 1 second in turns.
*/

// make the configuration of the RCC
void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

// make the configuration of the GPIO pin of the LED
void COLOR_TIMx_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_Configuration();

    // make the configuration of the GPIO pin of the LED
    RCC_APB2PeriphClockCmd(COLOR_TIM_GPIO_CLK, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
    
    // red
    GPIO_InitStructure.GPIO_Pin = COLOR_RED_TIM_LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(COLOR_RED_TIM_LED_PORT, &GPIO_InitStructure);

    // green
    GPIO_InitStructure.GPIO_Pin = COLOR_GREEN_TIM_LED_PIN;
    GPIO_Init(COLOR_GREEN_TIM_LED_PORT, &GPIO_InitStructure);

    // blue
    GPIO_InitStructure.GPIO_Pin = COLOR_BLUE_TIM_LED_PIN;
    GPIO_Init(COLOR_BLUE_TIM_LED_PORT, &GPIO_InitStructure);
}

// make the configuration of the PWM of the LED
void COLOR_PWM_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    // Initialize the time base structure for TIM3
    RCC_APB1PeriphClockCmd(COLOR_TIM_CLK, ENABLE);

    // Set the prescaler, period, and other parameters for TIM3
    TIM_TimeBaseStructure.TIM_Period = 255;
    TIM_TimeBaseStructure.TIM_Prescaler = 100;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(COLOR_TIMx, &TIM_TimeBaseStructure);

    // Initialize the output compare structure for TIM3
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    //  OC2 red
    TIM_OC2Init(COLOR_TIMx, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(COLOR_TIMx, TIM_OCPreload_Enable);

    //  OC3 green
    TIM_OC3Init(COLOR_TIMx, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(COLOR_TIMx, TIM_OCPreload_Enable);

    //  OC4 blue
    TIM_OC4Init(COLOR_TIMx, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(COLOR_TIMx, TIM_OCPreload_Enable);

    // Enable the ARR preload register and start the timer
    TIM_ARRPreloadConfig(COLOR_TIMx, ENABLE);
    TIM_Cmd(COLOR_TIMx, ENABLE);
}

// TIM4's configuration
void COLOR_TIMx4_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(COLOR_TIM4_CLK, ENABLE);

    // Initialize the time base structure for TIM4 and set the prescaler and period
    TIM_TimeBaseStructure.TIM_Period = 1800 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 5000 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(COLOR_TIMx4, &TIM_TimeBaseStructure);

    // Enable update interrupt
    TIM_ITConfig(COLOR_TIMx4, TIM_IT_Update, ENABLE);
    TIM_Cmd(COLOR_TIMx4, ENABLE);
}

// the number for the color
int currentColor = -1;

// TIM4's interrupt handler to update the color state
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(COLOR_TIMx4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(COLOR_TIMx4, TIM_IT_Update);

        // update the color state
        currentColor = (currentColor + 1) % 7;

        // set the color according to the current state
        switch (currentColor)
        {
            case COLOR_RED:
                COLOR_TIMx->CCR2 = 255;
                COLOR_TIMx->CCR3 = 0;
                COLOR_TIMx->CCR4 = 0;
                break;
            
            // The orange color is set by the mixture of red and yellow
            // Here we set the yellow in a smaller number to make the color more orange
            case COLOR_ORANGE:
                COLOR_TIMx->CCR2 = 255;
                COLOR_TIMx->CCR3 = 64;
                COLOR_TIMx->CCR4 = 0;
                break;

            case COLOR_YELLOW:
                COLOR_TIMx->CCR2 = 255;
                COLOR_TIMx->CCR3 = 255;
                COLOR_TIMx->CCR4 = 0;
                break;

            case COLOR_GREEN:  
                COLOR_TIMx->CCR2 = 0;
                COLOR_TIMx->CCR3 = 255;
                COLOR_TIMx->CCR4 = 0;
                break;

            // The cyan color is set by the mixture of blue and red
            case COLOR_CYAN:
                COLOR_TIMx->CCR2 = 0;
                COLOR_TIMx->CCR3 = 255;
                COLOR_TIMx->CCR4 = 255;
                break;

            case COLOR_BLUE:
                COLOR_TIMx->CCR2 = 0;
                COLOR_TIMx->CCR3 = 0;
                COLOR_TIMx->CCR4 = 255;
                break;

            // The purple color is set by the mixture of blue and red
            case COLOR_PURPLE:
                COLOR_TIMx->CCR2 = 128;
                COLOR_TIMx->CCR3 = 0;
                COLOR_TIMx->CCR4 = 255;
                break;
        }
    }
}
