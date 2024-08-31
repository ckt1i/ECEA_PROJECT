# include "stm32f10x.h"
#include "stm32f10x_gpio.h" 
#include "stm32f10x_tim.h" 

# include "bsp_led_breath.h"

/*
	This is the main function of the project. The project make the LED on the board to breath,
	which means the LED will gradually brighten and gradually dim.
*/

// main functions, the specific funcions is included in bsp_led_breath.c
int main(void)
{
	// initialize the GPIO outputs
	COLOR_TIMx_GPIO_Config();

	// initialize the TIM3
	COLOR_TIMx_MODE_Config();

	// initialize the TIM and NVIC
	BASIC_TIM_Init();

	BASIC_TIM_NVIC_Config();

	TIM_Cmd(BASIC_TIM, ENABLE);

	while(1);
}
