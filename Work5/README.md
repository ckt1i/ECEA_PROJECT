# Work5: Making 7-color lamp

## Basic Information

**Author**： Zheng ChangQian

**Date** 2024/8/30

## Function description

1. Use TIM3 to output PWM signals to control the full color LED to switch colors.

2. Use another TIM as a counter to make an interrupt every 1 second.

3. Control a state machine using interrupts to change the CCR (Capture/Compare Register) of a full-color LED.

4. Objective: Achieve a color cycle of red, orange, yellow, green, cyan, blue, and purple, switching colors every 1 second.

## Main files in `./User` directory:

1. `main.c`: The main program, which initializes the serial port and DMA, and then transmits the message stored in the FLASH to the PC.

2. `bsp_led_colors.h`: The header file for the full-color LED control function.

3. `bsp_led_colors.c`: The source file for the full-color LED control function, which uses PWM signals to control the LED.

4. `stm32f10x_conf.h` and `stm32f10x_it.h` and `stm32f10x_it.c`: The configuration files for the project.
