# ifndef     _BEEP_H_
# define     _BEEP_H_

#include "stm32f10x.h" 
#include "stm32f10x_conf.h" 

// define beeper's pin, port , and clock
#define BEEP_PIN   GPIO_Pin_8
#define BEEP_PORT  GPIOA
#define BEEP_CLK   RCC_APB2Periph_GPIOA

// define beeper's status
#define BEEP_ON  1
#define BEEP_OFF 0

// define beeper's frequency
void BEEP_Init(void);

// define beeper's function
void BEEP(uint8_t status);

# endif /*__BEEP_H*/
