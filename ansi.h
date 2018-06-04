#ifndef _ANSI_H_
#define _ANSI_H_

#include "struct.h"

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
void box (int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t style);
void minibox (int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t style, uint8_t n);
void drawBlock(struct Block block);

void stopWatchWindow(int8_t x1, int8_t y1, int8_t x2, int8_t y2, char str[], int8_t style);


#endif /* _ANSI_H_ */
