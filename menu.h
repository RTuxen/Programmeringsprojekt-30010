#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#ifndef _MENU_H_
#define _MENU_H_

#include "game.h"
#include "graphics.h"
#include "flashmemory.h"
#include "display.h"
#include "IO.h"
#include "sound.h"
#include "rtc.h"

void chooseMenuOptions(struct game_state_t* gs);
void chooseLevel(struct game_state_t* gs);
void chooseOptions(struct game_state_t* gs);
void chooseHighscore(struct game_state_t* gs);
void chooseHelp(struct game_state_t* gs);
void chooseGameOver(struct game_state_t* gs);
void chooseGameWon(struct game_state_t* gs);
void toggleMirror(struct game_state_t* gs);
void changeSpeed(struct game_state_t* gs);
void changeNumberOfPlayers(struct game_state_t* gs);
void changeController(struct game_state_t* gs);
#endif
