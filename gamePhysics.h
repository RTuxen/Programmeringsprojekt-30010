#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#ifndef _GAMEPHYSICS_H_
#define _GAMEPHYSICS_H_

#include "struct.h"

#include "menu.h"
#include "LUT.h"



int32_t moveBallX(struct ball_t * ball);
int32_t moveBallY(struct ball_t * ball);
void updateFallingObject(struct fallingObject_t *fallObject, struct player_t * striker, struct game_state_t* gs);
void updateBallPos(struct ball_t * ball,struct player_t *striker, struct level_t *level, struct game_state_t * gs,struct fallingObjectsType_t * fallObject_ptr);
void updateBallPos2Players(struct ball_t * ball,struct player_t *striker,struct player_t * striker2, struct level_t *level, struct game_state_t * gs, struct fallingObjectsType_t * fallObject_ptr);
uint16_t checkWallCollision(struct ball_t * ball,struct game_state_t *gs);
void checkPlayerCollision(struct ball_t * ball, struct player_t * striker, struct game_state_t * gs);
void checkBlockCollision(struct ball_t* ball, struct level_t* level, struct game_state_t * gs, struct fallingObjectsType_t *fallObject_ptr);


#endif /* _GAMEPHYSICS_H_ */
