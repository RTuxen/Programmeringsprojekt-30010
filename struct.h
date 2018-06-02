#ifndef _STRUCT_H_
#define _STRUCT_H_
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

struct ball_t {
    int32_t x, y, dx, dy;
};

struct vector_t {
    int32_t x, y;
};


#endif /*_STRUCT_H_*/
