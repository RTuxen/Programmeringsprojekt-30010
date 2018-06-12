#ifndef IO_H
#define IO_H
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "struct.h"

void initTimer100Hz();
void printTid();
void stopWatchControl(int8_t value);
void printSplit (uint8_t c, uint8_t s, uint8_t m, uint8_t h);
uint8_t get_flag();
uint8_t get_game_flag();

#endif	// IO_H
