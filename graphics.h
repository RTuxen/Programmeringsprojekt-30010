#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "struct.h"
#include "ansi.h"
#include "levels.h"

uint8_t strlens(char* text);
void window (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char str[], uint8_t style);
void box (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, int8_t style);
void minibox (int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t style, uint8_t n);
void stopWatchWindow(int8_t x1, int8_t y1, char str[], int8_t style);

//void textReturn(int8_t len);
//void compareString(char * text);

void commandList();
void userGuide();

void drawWalls ();
void drawball(struct ball_t * ball);
void drawPlayer(struct player_t *striker);
void drawBlock(struct block_t block);
void drawBlockMap(struct block_t *bricks);
void printfallObject(struct fallingObject_t *fallObject);
void drawMenuWindow();
void drawPlayWindow();
void drawOptionWindow(struct game_state_t* gs);
void drawHighscoreWindow(uint16_t* highscores);
void drawHelpWindow();
void drawGameOverWindow();
void drawGameWonWindow();
void drawWelcomeMessage();
void drawHighscoreMessage();
void drawOptionMessage();
void drawHelpMessage();
void drawTrophy();

#endif /* _GRAPHICS_H_ */
