#ifndef _ANSI_H_
#define _ANSI_H_


#include <string.h>
#include "LUT.h"
#include "struct.h"
#include "timer.h"
#define ESC 0x1B

void fgcolor(uint8_t foreground);
void bgcolor (uint8_t background);
void color (uint8_t foreground, uint8_t background);
void resetbgcolor();
void window (int8_t x1, int8_t y1, int8_t x2, int8_t y2, char str[], int8_t style);
void clrscr();
void clreol ();
void gotoxy(int8_t x, int8_t y);
void underline (int8_t on);
void blink (int8_t on);
void inverse (int8_t on);
void saveCursor();
void getSavedCursor();
void moveCursor(char dir, unsigned char n);
uint8_t strlens(char* text);
void box (int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t style);
void minibox (int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t style, uint8_t n);
void drawBlock(struct Block block);

void stopWatchWindow(int8_t x1, int8_t y1, char str[], int8_t style);
void textReturn(int8_t len);
void compareString(char * text);
void commandList();
void userGuide();


#endif /* _ANSI_H_ */
