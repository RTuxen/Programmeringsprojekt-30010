#ifndef _STRUCT_H_
#define _STRUCT_H_
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

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
struct Player {
	int32_t x;
	int32_t y;
	int8_t points;
	int8_t lifes;
	int8_t level;
};

struct Block {
	int8_t lifes;
	int8_t x;
	int8_t y;
};

struct Level {
	struct Block blocks[128];
	int8_t lifes;
	int8_t wall[4];
};

#endif /*_STRUCT_H_*/
