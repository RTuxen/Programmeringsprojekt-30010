#ifndef IO_H
#define IO_H

#include "struct.h"

void initTimer100Hz();
void TIM2_IRQHandler(void);
void printTid();
void stopWatchControl(int8_t value);
void printSplit (int8_t c, int8_t s, int8_t m, int8_t h);
void stopWatchControl(int8_t value);


#endif	// IO_H
