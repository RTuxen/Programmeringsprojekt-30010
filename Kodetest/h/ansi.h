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
void clrscr();
void clreol ();
void gotoxy(uint16_t x, uint16_t y);
void underline (int8_t on);
void blink (int8_t on);
void inverse (int8_t on);
void saveCursor();
void getSavedCursor();
void moveCursor(char dir, unsigned char n);
void hideCursor();
void showCursor();


#endif /* _ANSI_H_ */
