# Work3: Beeper for reporting the time

## Basic Information

**Author**： Zheng ChangQian

**Date** 2024/8/29

## Function description

1. A time-counter function using the method of systick to count time for 0.25 second.
2. Make beeper start a n time short beep and a long beep, n equals to the last number of student's ID mod 5 and then plus 1.
3. The time of a short beep is 0.25 second and the time of a long beep is 1 second.
4. When the beeper is working, the red LED will also light up.

## Main files in `./User` directory:

- `main.c`: The main function of the program, which initializes the system and starts the beeper.
- `beeper.c`: The function of beeper, which includes the time-counter function and the beep function.
- `beeper.h`: The header file of beeper, which includes the function declaration of beeper.
- `stm32f10x_conf.h`and`stm32f10x_it.h`and`stm32f10x_it.c`: The configuration files for the project.
