#ifndef _GAMEPHYSICS_H_
#define _GAMEPHYSICS_H_

#include "struct.h"
#include "IO.h"
#include "graphics.h"

void initbold (struct ball_t* ball, int32_t x, int32_t y, int32_t dx, int32_t dy);
void initPlayer(struct player_t * striker, uint8_t x, uint8_t y);
uint8_t updateBallPos(struct ball_t * ball,struct player_t *striker, int8_t x1 , int8_t y1,int8_t x2,int8_t y2);
void updatePlayerPos(struct player_t *striker);
int8_t checkWallCollision(struct ball_t * ball, int8_t x1 , int8_t y1,int8_t x2,int8_t y2);
uint8_t checkPlayerCollision(struct ball_t * ball, struct player_t * striker);


#endif /* _GAMEPHYSICS_H_ */
