# include "bsp_systick.h"
#include "stm32f10x.h" 
#include "stm32f10x_conf.h" 


// Here we use SysTick to generate a 1ms interrupt, 
// and then use the interrupt to count the number of milliseconds
void SysTick_Delay_ms(uint32_t ms)
{
    uint32_t i;

    // Enable SysTick and set the reload register to 1ms
    SysTick_Config(SystemCoreClock/1000);

    // Wait for the SysTick counter to reach the reload value
    for(i=0;i<ms;i++)
    {
        while(!(SysTick->CTRL & 0x00010000));
    }

    // Disable SysTick
    SysTick->CTRL = 0x00;
    SysTick->LOAD = 0x00;
}
