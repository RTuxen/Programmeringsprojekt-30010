#ifndef _MENU_H_
#define _MENU_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "graphics.h"
#include "IO.h"
#include "ansi.h"
#include "display.h"
#include "gamePhysics.h"

void chooseMenuOptions(uint8_t score);
void chooseLevel();
void chooseOptions();
void chooseHighscore();
void chooseHelp();
void chooseGameOver(uint8_t score, uint8_t levelNum, uint8_t* buffer);
uint8_t changeSpeed(uint8_t changeValue);

void drawMenuWindow();
void drawPlayWindow();
void drawOptionWindow();
void drawHighscoreWindow(uint8_t *highscores);
void drawHelpWindow();
void drawGameOverWindow();

#endif
