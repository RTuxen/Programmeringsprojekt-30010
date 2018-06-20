#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#ifndef _GAME_H_
#define _GAME_H_

#include "struct.h"
#include "gamePhysics.h"


void initGameState(struct game_state_t* gs);
void initBall (struct ball_t* ball, int32_t x, int32_t y, int32_t speed);
void initFallObject(struct fallingObjectsType_t * fallObjectArray);
void initPlayer(struct player_t * striker, uint16_t x, uint16_t y);
void initLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level, struct game_state_t* gs);
void initLevel2Players(struct ball_t *ball,struct ball_t * ball2, struct player_t *striker, struct player_t *striker2, struct level_t *level, struct game_state_t* gs);
void playGame(struct game_state_t* gs);
void restartLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level,struct fallingObjectsType_t * fallObjectArray);
void restartLevel2Players(struct ball_t *ball, struct ball_t * ball2, struct player_t *striker, struct player_t * striker2, struct level_t *level,struct fallingObjectsType_t * fallObjectArray);
void updatePlayerPosPotentiometer(struct player_t * striker, struct game_state_t * gs, int8_t playerNo);
void updatePlayerPos(struct player_t *striker, struct game_state_t* gs);
void updatePlayerPosI2C(struct player_t * striker, struct game_state_t * gs);
void bossKey();


#endif /* _GAME_H_ */
