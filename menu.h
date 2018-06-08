#ifndef _MENU_H_
#define _MENU_H_
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "graphics.h"
#include "IO.h"

void chooseMenuOptions();
void chooseLevel();
void chooseOptions();
void chooseHighscore();
void chooseHelp();

int8_t drawMenuWindow(int8_t x1, int8_t y1, int8_t style);
void drawPlayWindow(int8_t x1, int8_t y1, int8_t style);
void drawOptionWindow(int8_t x1, int8_t y1, int8_t style);
void drawHighscoreWindow(int8_t x1, int8_t y1, int8_t style, uint8_t *highscores);
void drawHelpWindow();




#endif
