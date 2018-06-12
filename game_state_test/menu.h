#ifndef _MENU_H_
#define _MENU_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "graphics.h"
#include "IO.h"
#include "ansi.h"
#include "display.h"
#include "gamePhysics.h"

void chooseMenuOptions(struct game_state_t* gs);
void chooseLevel(struct game_state_t* gs);
void chooseOptions(struct game_state_t* gs);
void chooseHighscore(struct game_state_t* gs);
void chooseHelp(struct game_state_t* gs);
void chooseGameOver(struct game_state_t* gs, uint8_t* buffer);
void changeSpeed(struct game_state_t* gs);

void drawMenuWindow();
void drawPlayWindow();
void drawOptionWindow(uint8_t speed);
void drawHighscoreWindow(uint8_t* highscores);
void drawHelpWindow();
void drawGameOverWindow();

#endif
