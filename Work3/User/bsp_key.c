# include "stm32f10x.h" 
# include "stm32f10x_conf.h" 
# include "bsp_key.h"

# define KEY_ON 1
# define KEY_OFF 0

/*
Here we packed the key's function into the file bsp_key.c for a better organization
*/ 

// define the debouncing function for the key
uint8_t Key_Scan(GPIO_TypeDef * GPIOx , uint16_t GPIO_Pin)
{
	// when the key is pressed, the key will set K
	if (GPIO_ReadInputDataBit(GPIOx , GPIO_Pin) == KEY_ON)
	{
		while (GPIO_ReadInputDataBit(GPIOx , GPIO_Pin) == KEY_ON)
		{
			;	// wait for the key to be released
		}
		return KEY_ON ;
	}
	else return KEY_OFF ;
}
