# ifndef __BSP_KEY_H
# define __BSP_KEY_H

# include "stm32f10x.h"

// define the key: key1 connects to the PA0
#define KEY1_GPIO_CLK RCC_APB2Periph_GPIOA
#define KEY1_GPIO_PORT GPIOA
#define KEY1_GPIO_PIN GPIO_Pin_0

// define the key: key2 connects to the PC13
#define KEY2_GPIO_CLK RCC_APB2Periph_GPIOC
#define KEY2_GPIO_PORT GPIOC
#define KEY2_GPIO_PIN GPIO_Pin_13

// scan the key
uint8_t Key_Scan(GPIO_TypeDef * GPIOx , uint16_t GPIO_Pin); 

# endif 
