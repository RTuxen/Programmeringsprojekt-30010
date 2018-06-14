#ifndef _GAMEPHYSICS_H_
#define _GAMEPHYSICS_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "struct.h"
#include "IO.h"
#include "ansi.h"
#include "LUT.h"
#include "graphics.h"
#include "levels.h"
#include "display.h"
#include "menu.h"
#include "timer.h"

void initGameState(struct game_state_t* gs);
void initBall (struct ball_t* ball, int32_t x, int32_t y, int32_t speed);
void initPlayer(struct player_t * striker, uint16_t x, uint16_t y);
void initLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level, struct game_state_t* gs);
void playGame(struct game_state_t* gs);
void restartLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level);

void updateBallPos(struct ball_t * ball,struct player_t *striker, struct level_t *level, struct game_state_t * gs, struct fallingObjectsType *fallObject_ptr);
void updatePlayerPos(struct player_t *striker, struct game_state_t* gs);

uint16_t checkWallCollision(struct ball_t * ball);
uint16_t checkPlayerCollision(struct ball_t * ball, struct player_t * striker);
uint16_t checkBlockCollision(struct ball_t* ball, struct level_t* level, struct game_state_t * gs, struct fallingObjectsType *fallObject_ptr);
void CheckHitWithPlayer(struct object *fallObject, struct player_t * striker, struct game_state_t* gs);
void bossKey();


#endif /* _GAMEPHYSICS_H_ */
