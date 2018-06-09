#ifndef _STRUCT_H_
#define _STRUCT_H_
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#define X1 1
#define Y1 1
#define X2 60
#define Y2 241

//#define X2 40
//#define Y2 119



struct vector_t {
    int32_t x, y;
};

struct ball_t {
    int32_t x;
    int32_t y;
    struct vector_t vec;
};


struct timepoint {
    uint8_t hours, minutes, seconds, centiseconds;
};
volatile struct timepoint tid; //Global variables

// theoretical structs
struct player_t {
	int32_t x;
	int32_t y;
	int8_t points;
	int8_t lifes;
	int8_t level;
};

struct block_t {
	uint16_t x;
	uint16_t y;
	uint8_t lifes;
};

struct level_t {
	struct block_t blocks[128];
	uint8_t lifes;
};

#endif /*_STRUCT_H_*/
