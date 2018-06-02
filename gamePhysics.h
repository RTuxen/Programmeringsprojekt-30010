#ifndef _GAMEPHYSICS_H_
#define _GAMEPHYSICS_H_

#include "struct.h"



void update(struct ball_t * ball, int8_t hit,int8_t x1 , int8_t y1,int8_t x2,int8_t y2);
void drawball(struct ball_t * ball);
int8_t checkEdge(struct ball_t * ball, int8_t x1 , int8_t y1,int8_t x2,int8_t y2);


#endif /* _GAMEPHYSICS_H_ */
