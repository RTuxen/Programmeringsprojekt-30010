#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#ifndef IO66_H
#define IO66_H

#include "struct.h"
#include "timer.h"

#define RED (0x0001 << 4)
#define GREEN (0x0001 << 7)
#define BLUE (0x0001 << 9)

void initJoystick();
int8_t readJoyStick();
int8_t readJoyStickContinous();
void initLED();
void turnOffLED();
void setLed(struct game_state_t* gs);
void initADC();
uint16_t readADC_pa0();
uint16_t readADC_pa1();
uint8_t readKeyboard();
void initBuzzer();
void load_sound(const uint16_t* sound, const uint8_t* duration);

#endif	// IO66_H
