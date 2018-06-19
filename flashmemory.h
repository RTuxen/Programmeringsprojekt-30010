#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#ifndef FLASHMEMORY_H_INCLUDED
#define FLASHMEMORY_H_INCLUDED

#include "struct.h"

void writeFlash(struct game_state_t* gs);
void readFlash(struct game_state_t* gs);

#endif /* FLASHMEMORY_H_INCLUDED */
