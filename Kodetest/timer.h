#ifndef IO_H
#define IO_H
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "struct.h"

void initTimer100Hz();
void initTimerPWM();
void setTimer(uint8_t difficulty, uint8_t levelspeed);
void setFreq(uint16_t freq);
void printTid();
void stopWatchControl(int8_t value);
void printSplit (uint16_t ms, uint8_t s, uint8_t m, uint8_t h);
uint8_t get_flag();
uint8_t get_game_flag();

#endif	// IO_H
