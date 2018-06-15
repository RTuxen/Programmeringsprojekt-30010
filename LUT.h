#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#ifndef LUT_H
#define LUT_H

// === LUT SIZES ===
#define SIN_SIZE 512

#include "struct.h"


#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a) * (b) >> FIX14_SHIFT )
#define FIX14_DIV(a ,b) ( ((a) << FIX14_SHIFT ) / (b) )



// === LUT DECLARATIONS ===
extern const signed short SIN[512];


int32_t expand(int32_t i);
void printFix (int32_t i);
int32_t sinus(int32_t vinkel);
int32_t cosinus(int32_t vinkel);
void initVector(struct vector_t *v, int32_t a,int32_t b);
void rotat(struct vector_t *vec, int32_t vinkel);

#endif	// LUT_H
