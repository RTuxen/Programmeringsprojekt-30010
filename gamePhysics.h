#ifndef _GAMEPHYSICS_H_
#define _GAMEPHYSICS_H_

#include "struct.h"
#include "IO.h"
#include "graphics.h"
#include "levels.h"
#include "display.h"
#include "menu.h"

void initBall (struct ball_t* ball, int32_t x, int32_t y, int32_t dx, int32_t dy);
void initPlayer(struct player_t * striker, uint16_t x, uint16_t y, uint8_t levelNum);
void playGame(uint8_t levelNum);
void initLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level);
void restartLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level);

uint16_t updateBallPos(struct ball_t * ball,struct player_t *striker, struct level_t *level);
void updatePlayerPos(struct player_t *striker);

uint16_t checkWallCollision(struct ball_t * ball);
uint16_t checkPlayerCollision(struct ball_t * ball, struct player_t * striker);
uint16_t checkBlockCollision(struct ball_t* ball, struct level_t* level, struct player_t * striker);


#endif /* _GAMEPHYSICS_H_ */
