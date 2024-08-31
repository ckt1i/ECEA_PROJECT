#include "stm32f10x.h" 
#include "stm32f10x_conf.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_systick.h"
#include "beep.h"

/*
	This is the main function of the project. It make the function of homework 3.
	Here, because the function is more complex, so I packed them into different files 
	to make the code more readable.
*/

int main(void)
{	
	// Set the count number i
	uint8_t i = 0;
	
	// Initialize LED and Beep
	LED_initialize();
	BEEP_Init();


	// Make a short BEEP and LED blink 4 times with 1 second interval and 0.25 second on time
	// When the BEEP is on, the LED is also 
	// my last number of id is 3, 3 mod 5 plus 1 is 4 , so the id mode is 4
	while(i < 4)
	{
		// tun on the LED and BEEP for 0.25 second
		LEDR_on();
		BEEP(1);
		SysTick_Delay_ms(25);
		LED_off();
		BEEP(0);

		// then delay 1 second
		SysTick_Delay_ms(100);
		i++;
	}

	// Make a long BEEP and LED blink 4 times with 1 second interval
	LEDR_on();
	BEEP(1);
	SysTick_Delay_ms(100);
	BEEP(0);
	LED_off();
}

