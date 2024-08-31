#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

// define the LED's clock and port
#define LED_GPIO_CLK RCC_APB2Periph_GPIOB
#define LED_GPIO_PORT GPIOB

// define the LED's pin: LEDG connects to the PB0, LEDB connects to the PB1, LEDR connects to the PB5
#define LEDG_GPIO_PIN GPIO_Pin_0
#define LEDB_GPIO_PIN GPIO_Pin_1
#define LEDR_GPIO_PIN GPIO_Pin_5

// define the key's status
#define KEY_ON 1
#define KEY_OFF 0

void LED_initialize(void);

// define the LED's function in color red, green, blue
void LEDR_on(void);
void LEDG_on(void);
void LEDB_on(void);

// define the LED's function in mixed color of  and pink , yellow , cray and white
void LEDY_on(void);
void LEDP_on(void);
void LEDC_on(void);

// define the LED's function in on with default color white
void LED_on(void);

// define the LED's function in off
void LED_off(void);

# endif /*__BSP_LED_H*/

