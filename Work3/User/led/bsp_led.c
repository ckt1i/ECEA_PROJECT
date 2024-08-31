#include "stm32f10x.h" 
#include "stm32f10x_conf.h" 
# include "bsp_led.h"
# include "bsp_key.h"

void LED_initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// Enable the clock for the GPIO ports used for KEY1, KEY2, and LED
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK|LED_GPIO_CLK,ENABLE);
	
	// Configure the GPIO pins for KEY1, KEY2, and LED as input and output respectively
	GPIO_InitStructure.GPIO_Pin = LEDR_GPIO_PIN|LEDG_GPIO_PIN|LEDB_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	// Initialize the GPIO pins
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
	
	// Set the KEY1 and KEY2 pins to GPIO_Mode_In_FLOATING with output rate of 10MHz
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	
	// Initialize the GPIO pins
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);
	
	LED_off();
}

// define the LED's function in color red, green, blue
void LEDR_on(void)
{
	// Turn on the red LED
	GPIO_WriteBit(LED_GPIO_PORT,LEDR_GPIO_PIN,Bit_RESET);
}

void LEDG_on(void)
{
	// Turn on the green LED
	GPIO_WriteBit(LED_GPIO_PORT,LEDG_GPIO_PIN,Bit_RESET);
}

void LEDB_on(void)
{
	// Turn on the blue LED
	GPIO_WriteBit(LED_GPIO_PORT,LEDB_GPIO_PIN,Bit_RESET);
}

// define the LED's function in mixed color of  yellow , magenta , cray
void LEDY_on(void)
{
	// Turn on the yellow LED
	GPIO_WriteBit(LED_GPIO_PORT,LEDG_GPIO_PIN|LEDB_GPIO_PIN,Bit_RESET);
}

void LEDM_on(void)
{
	// Turn on the magenta LED
	GPIO_WriteBit(LED_GPIO_PORT,LEDR_GPIO_PIN|LEDB_GPIO_PIN,Bit_RESET);
}

void LEDC_on(void)
{
	// Turn on the cray LED
	GPIO_WriteBit(LED_GPIO_PORT,LEDR_GPIO_PIN|LEDG_GPIO_PIN,Bit_RESET);
}

// define the LED's function in on with default color white
void LED_on(void)
{
	// Turn on the white LED
	GPIO_WriteBit(LED_GPIO_PORT,LEDR_GPIO_PIN|LEDG_GPIO_PIN|LEDB_GPIO_PIN,Bit_RESET);
}

// define the LED's function in off
void LED_off(void)
{
	// Turn off the LED
	GPIO_WriteBit(LED_GPIO_PORT,LEDR_GPIO_PIN|LEDG_GPIO_PIN|LEDB_GPIO_PIN,Bit_SET);	
}
