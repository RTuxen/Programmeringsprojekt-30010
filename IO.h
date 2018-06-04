#ifndef IO_H
#define IO_H

#include "struct.h"
#define RED (0x0001 << 4)
#define GREEN (0x0001 << 7)
#define BLUE (0x0001 << 9)

void initJoystick();
int8_t readJoyStick();
void initLED();
void setLed(int8_t value);

#endif	// IO_H
