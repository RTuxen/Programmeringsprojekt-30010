#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"


void fgcolor(uint8_t foreground) {
	/*  Value      foreground     Value     foreground
	 ------------------------------------------------
	 0        Black            8       Dark Gray
	 1        Red              9       Light Red
	 2        Green           10       Light Green
	 3        Brown           11       Yellow
	 4        Blue            12       Light Blue
	 5        Purple          13       Light Purple
	 6        Cyan            14       Light Cyan
	 7        Light Gray      15       White
	 */
	int type = 22; // normal text
	if (foreground > 7) {
		type = 1; // bold text
		foreground -= 8;
	}
	printf("%c[%d;%dm", ESC, type, foreground + 30);
}

void bgcolor(uint8_t background) {
	/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
	 Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
	 The designers of HyperTerminal, however, preferred black text on white background, which is why
	 the colors are initially like that, but when the background color is first changed there is no
	 way comming back.
	 Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.
	 Value      Color
	 ------------------
	 0        Black
	 1        Red
	 2        Green
	 3        Brown
	 4        Blue
	 5        Purple
	 6        Cyan
	 7        Gray
	 */
	printf("%c[%dm", ESC, background + 40);
}

void color(uint8_t foreground, uint8_t background) {
	// combination of fgcolor() and bgcolor() - uses less bandwidth
	int type = 22; // normal text
	if (foreground > 7) {
		type = 1; // bold text
		foreground -= 8;
	}
	printf("%c[%d;%d;%dm", ESC, type, foreground + 30, background + 40);
}

void resetbgcolor() {
	// gray on black text, no underline, no blink, no reverse
	printf("%c[m", ESC);
}


void clrscr()
{
    printf("%c[2J",ESC);
}

void clreol ()
{
    printf("%c[K",ESC);
}

void gotoxy(int8_t x, int8_t y)
{
    printf("%c[%d;%dH", ESC, x, y);
}

void underline (int8_t on)
{
    if (on){
        printf("%c[4m",ESC);
    } else{
        printf("%c[24m",ESC);
    }
}

void blink (int8_t on)
{
    if (on){
        printf("%c[5m",ESC);
    } else{
        printf("%c[25m",ESC);
    }
}

void inverse (int8_t on){
    if (on){
        printf("%c[7m",ESC);
    } else{
        printf("%c[27m",ESC);
    }
}

void saveCursor() { // Save the position of the cursor
	printf("%c[s", ESC);
}

void getSavedCursor() { // Get the last saved position
	printf("%c[u", ESC);
}

/*
dir = 'A' for up
dir= 'B' for down
dir = 'C' for forward
dir = 'D' for back

*/

void moveCursor(char dir, unsigned char n) { // Move cursor in some direction
	printf("%c[%d%c", ESC, n, dir);
}

