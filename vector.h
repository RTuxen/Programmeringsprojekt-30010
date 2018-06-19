#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "LUT.h"
#include "struct.h"


#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a) * (b) >> FIX14_SHIFT )
#define FIX14_DIV(a ,b) ( ((a) << FIX14_SHIFT )
#define ESC 0x1B

int32_t expand(int32_t i);
void printFix (int32_t i);
int32_t sinus(int32_t vinkel);
int32_t cosinus(int32_t vinkel);
void initVector(struct vector_t *v, int32_t a,int32_t b);
void rotat(struct vector_t *vec, int32_t vinkel);


#endif /* _ANSI_H_ */

