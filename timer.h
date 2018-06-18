#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#ifndef TIMER_H
#define TIMER_H

#include "struct.h"

void initTimer1000Hz();
void printTid();
void setTimer(uint8_t difficulty, uint8_t levelspeed);
void setTimerDefault();
//void stopWatchControl(int8_t value);
//void printSplit (uint16_t ms, uint8_t s, uint8_t m, uint8_t h);
void initTimerPWM();
void setFreq(uint16_t freq);
uint8_t get_flag();
uint8_t get_game_flag();

#endif	// TIMER_H
