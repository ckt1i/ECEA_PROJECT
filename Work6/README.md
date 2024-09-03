# Work6: Make a multiple color breathing lamp

## Basic Information

**Author**： Zheng ChangQian

**Date** 2024/8/30

## Function description

1. Make a 4-color (red , green, blue, yellow) breathing lamp, the breathing cycle is 1.x seconds. (x is the last digit of the ID)

2. The cycle of updating the CCR is 


## Main files in `./User` directory:

1. `main.c`: The main program, which initializes the serial port and DMA, and then transmits the message stored in the FLASH to the PC.

2. `bsp_led_breath.h`: The header file for the breathing lamp control function, which uses PWM signals to control the LED.

3. `bsp_led_breath.c`: The source file for the breathing lamp control function, which uses PWM signals to control the LED.

4. `stm32f10x_conf.h` and `stm32f10x_it.h` and `stm32f10x_it.c`: The configuration files for the project.
