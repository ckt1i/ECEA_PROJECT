# Work4: Using serial port to print text

## Basic Information

**Author**： Zheng ChangQian

**Date** 2024/8/30

## Function description

1. Transmit a message to the PC using direct serial port configuration.

2. Store a message in FLASH and use DMA to configure the serial port to transmit it to the PC.

## Main files in `./User` directory:

1. `main.c`: The main program, which initializes the serial port and DMA, and then transmits the message stored in the FLASH to the PC.

2. `bsp_usart.c`: The serial port driver, which initializes the serial port and handles the transmission and reception of data.

3. `bsp_usart.h`: The serial port driver header file, which defines the serial port configuration and function prototypes.

4. `stm32f10x_conf.h` and `stm32f10x_it.h` and `stm32f10x_it.c`: The configuration files for the project.
