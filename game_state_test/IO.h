#ifndef IO66_H
#define IO66_H

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "struct.h"
#define RED (0x0001 << 4)
#define GREEN (0x0001 << 7)
#define BLUE (0x0001 << 9)

void initJoystick();
int8_t readJoyStick();
int8_t readJoyStickContinous();
void initBuzzer();
void setFreq(uint16_t freq);
void initLED();
void setLed(int8_t value);
void initADC();
uint16_t readADC_pa0();
uint16_t readADC_pa1();

#endif	// IO_H
