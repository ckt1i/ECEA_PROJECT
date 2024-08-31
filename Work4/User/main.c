# include "stm32f10x.h"
# include "stm32f10x_usart.h"
# include "bsp_usart.h"

/*
	Here is the main function of the program. 
	The program is to write a string into the Flash's storing room and read it out,
	and send it to the computer through the USART if the computer sends the corresponding sentences
	by the corresponding program.
*/

// define the starting address of the Flash's storing room
#define FLASH_STRING_ADDRESS 0x08008000

int main(void)
{	
	//Setting the arguments
	uint32_t flashAddress = FLASH_STRING_ADDRESS;
  	const char *flashString = "I'm fine, Thank you! And U?(sending from FLASH!)";
  	const char *sourceAddress = flashString;

	// initialize the USART
	USART_Config();

	Usart_SendString(USART1, "Hello! How are U?");
	
	// unlock the Flash program erase/write
	FLASH_Unlock(); 
	// erase the whole Flash
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

  	while (*sourceAddress != '\0') {
		FLASH_ProgramWord(flashAddress, *sourceAddress);
		flashAddress += 4; // Increment by 4 bytes for each word
		sourceAddress++;
  	}
	// lock the Flash program erase/write
	FLASH_Lock();

	// Transmit the stored string using DMA
    Usart_SendStringDMA(USART1, flashString);

	// wait for the DMA transfer to complete
    while (1) {}
}

