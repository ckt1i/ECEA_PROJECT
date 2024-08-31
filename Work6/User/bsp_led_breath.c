#include "bsp_led_breath.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h" 
#include "stm32f10x_rcc.h" 
#include "misc.h"
#include "stm32f10x_tim.h"

/*
    Here's the specification of the LED breath function.
*/

// RCC configuration
void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

// GPIO output configuration
void COLOR_TIMx_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_Configuration();
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

// TIM configuration
void COLOR_TIMx_MODE_Config(void)
{
    // TIM3 timebase initialization and counting enabled
    
    TIM_OCInitTypeDef TIM_OCInitStructure;

    // This statement is in the next part of the code, however,
    //it is placed here to avoid compile errors.
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    RCC_APB1PeriphClockCmd(COLOR_TIM_CLK, ENABLE);

    /*
        Here I set the period to 250, which means that the LED will change the brightness 250 times,
        which means the total loop of breath will take 500 interupts to complete.
    */
    TIM_TimeBaseStructure.TIM_Prescaler = 7;
    TIM_TimeBaseStructure.TIM_Period = 250; 
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(COLOR_TIM, &TIM_TimeBaseStructure);

    TIM_ARRPreloadConfig(COLOR_TIM, ENABLE);
    TIM_Cmd(COLOR_TIM, ENABLE);

    // TIM3 output initialization and output enablement

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    TIM_OC2Init(COLOR_TIM, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable);

    TIM_OC3Init(COLOR_TIM, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable);

    TIM_OC4Init(COLOR_TIM, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable);
}

// setting the time of loop for the breath
void BASIC_TIM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE);
	/*
        The main clock is 72M, I set the prescaler to 1440, then the clock frequency is 50K.
        Then I set the period to 13, so the frequency of the PWM is 500/13Hz, 
        which means the PWM period is 2.6ms.
        Each color's breath takes 500 PWM periods, which is 1.3s in total, 
        which is 1.x and x corresponds to my last number of school ID
    */
    TIM_TimeBaseStructure.TIM_Prescaler = 1440 - 1;
    TIM_TimeBaseStructure.TIM_Period = 13;
	TIM_TimeBaseInit(BASIC_TIM,&TIM_TimeBaseStructure);

	TIM_ARRPreloadConfig(BASIC_TIM,ENABLE);
	TIM_Cmd(BASIC_TIM,ENABLE);

    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
    TIM_ITConfig(BASIC_TIM, TIM_IT_Update, ENABLE);
}

uint16_t breathCounter = 0;

uint8_t breathDirection = 1; 

int currentColor=0;


// setting the function of breath
void TIM6_IRQHandler(void)
{
    if (TIM_GetITStatus(BASIC_TIM, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(BASIC_TIM, TIM_IT_Update);
        
        // Update the PWM duty cycle (CCR values) based on the currentColor
        switch (currentColor) {
            case COLOR_RED:
                TIM_SetCompare2(COLOR_TIM, breathCounter); // Red
                TIM_SetCompare3(COLOR_TIM, 0);
                TIM_SetCompare4(COLOR_TIM, 0);
                break;
            case COLOR_GREEN:
                TIM_SetCompare2(COLOR_TIM, 0);
                TIM_SetCompare3(COLOR_TIM, breathCounter); // Green
                TIM_SetCompare4(COLOR_TIM, 0);
                break;
            case COLOR_BLUE:
                TIM_SetCompare2(COLOR_TIM, 0);
                TIM_SetCompare3(COLOR_TIM, 0);
                TIM_SetCompare4(COLOR_TIM, breathCounter); // Blue
                break;
            case COLOR_WHITE:
                TIM_SetCompare2(COLOR_TIM, breathCounter); // Red
                TIM_SetCompare3(COLOR_TIM, breathCounter); // Green
                TIM_SetCompare4(COLOR_TIM, breathCounter); // Blue
                break;
            default:
                break;
        }

        // Update the breathCounter and direction
        // when the breathDirection is true, the led will light up gradually
        if (breathDirection) 
		{
            breathCounter++;
            // when the led is fully lit, the led will starting dim
            if (breathCounter >= 250) 
			{
                breathCounter = 250;
                breathDirection = 0;
            }
        } 
        else // when the breathDirection is false, the led will dim gradually
        {
            breathCounter--;
            // when the led is fully dim, the led will starting light up
            if (breathCounter == 0) 
						{
                breathCounter = 0;
                breathDirection = 1;
                currentColor = (currentColor + 1) % 4;
            }
        }
    }
}

// NVIC settings, interrupt enablement and priority initialization for TIM6
void BASIC_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}
