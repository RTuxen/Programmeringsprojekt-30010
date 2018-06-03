#ifndef _GAMEPHYSICS_H_
#define _GAMEPHYSICS_H_

#include "struct.h"


void initbold (struct ball_t* ball, int32_t x, int32_t y, int32_t dx, int32_t dy);
void update(struct ball_t * ball,int8_t x1 , int8_t y1,int8_t x2,int8_t y2);
void drawball(struct ball_t * ball);
int8_t checkWallCollision(struct ball_t * ball, int8_t x1 , int8_t y1,int8_t x2,int8_t y2);


#endif /* _GAMEPHYSICS_H_ */
