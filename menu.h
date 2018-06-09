#ifndef _MENU_H_
#define _MENU_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "graphics.h"
#include "IO.h"
#include "ansi.h"

void chooseMenuOptions();
void chooseLevel();
void chooseOptions();
void chooseHighscore();
void chooseHelp();
uint8_t changeSpeed();

void drawMenuWindow();
void drawPlayWindow();
void drawOptionWindow();
void drawHighscoreWindow(uint8_t *highscores);
void drawHelpWindow();

#endif
