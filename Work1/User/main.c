#include "stm32f10x.h"

/*
	This is the main function of the program. I initially use the libraries of the sample LED project, 
	however, it now has been abandoned, so maybe you can delete the /User/LED directory.
	The function is simple so I didnn't seperate it into different files.
*/

// define the KEY1's GPIO settings
#define KEY1_GPIO_CLK RCC_APB2Periph_GPIOA
#define KEY1_GPIO_PORT GPIOA
#define KEY1_GPIO_PIN GPIO_Pin_0

// define the KEY2's GPIO settings
#define KEY2_GPIO_CLK RCC_APB2Periph_GPIOC
#define KEY2_GPIO_PORT GPIOC
#define KEY2_GPIO_PIN GPIO_Pin_13

// define the LED's GPIO settings
#define LED_GPIO_CLK RCC_APB2Periph_GPIOB
#define LED_GPIO_PORT GPIOB
#define LEDG_GPIO_PIN GPIO_Pin_0
#define LEDB_GPIO_PIN GPIO_Pin_1
#define LEDR_GPIO_PIN GPIO_Pin_5

// define the KEY's status
#define KEY_ON 1
#define KEY_OFF 0

// define the KEY's scan function, this function achives a debounce effect of the keys
uint8_t Key_Scan(GPIO_TypeDef * GPIOx , uint16_t GPIO_Pin)
{
	// The function will keep scanning the key until the key is released
	if (GPIO_ReadInputDataBit(GPIOx , GPIO_Pin) == KEY_ON)
	{
		while (GPIO_ReadInputDataBit(GPIOx , GPIO_Pin) == KEY_ON)
		{
			return KEY_ON ;
		}
	}
	else return KEY_OFF ;
}

// initialize the GPIOs
void initialize(void)
{
	// define the GPIO's structure
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// enable the GPIO's clock
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK|LED_GPIO_CLK,ENABLE);
	
	// initialize the LED's GPIO
	GPIO_InitStructure.GPIO_Pin = LEDR_GPIO_PIN|LEDG_GPIO_PIN|LEDB_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
	
	// initialize the KEY1's GPIO
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	
	// initialize the KEY2's GPIO
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);
}

int main(void)
{	
	// make the initialization
	initialize();
	
	// The main loop of the program: 
	//when KEY1 is pressed, the LED will be turned off, otherwise, it will be turned on
	while(1)
	{
		// when KEY1 is pressed, the LED will be turned on
		if(Key_Scan(KEY1_GPIO_PORT , KEY1_GPIO_PIN) == KEY_ON)
		{	
			// turn on the LED by resetting the corresponding GPIO pin
			GPIO_WriteBit(LED_GPIO_PORT,LEDB_GPIO_PIN,Bit_RESET);
		}
		else //otherwise, the LED will be turned off
		{
			// turn off the LED by setting the corresponding GPIO pin
			GPIO_WriteBit(LED_GPIO_PORT,LEDR_GPIO_PIN|LEDG_GPIO_PIN|LEDB_GPIO_PIN,Bit_SET);
		}
	};
}

