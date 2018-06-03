#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include <stdio.h>
#include <time.h>

#include <string.h>
#include "ansi.h"
#include "LUT.h"
#include "struct.h"


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


void window (int8_t x1, int8_t y1, int8_t x2, int8_t y2, char str[], int8_t style){ // Draws window with text in the middle
int8_t len = strlen(str);
int8_t i, j;
int8_t dx = x2-x1;
int8_t dy = y2-y1;


if (x1 >= x2 || y1 >= y2 || len > dy-2){
    return;
}

int8_t incre = dy/2 - len/2;
gotoxy(x1,y1);

for (i=1; i<=dx; i++){
    if (i==1) {
        printf("%c",style? 201:218);
    } else if(i==dx){
        printf("%c",style? 200:192);
    } else{
        printf("%c",style? 186:179);
    }
    for ( j=1; j<=dy; j++){
        if (i==1){
            if (j < incre){
				printf("%c",style? 205:196);
			} else if (j==incre) {
                printf("%c",style? 185:180);
            } else if ( j-1-incre < len){
                inverse(1);
                printf("%c",str[j-1-incre]);
                inverse(0);
            } else if (j-1-incre==len){
                printf("%c",style? 204:195);
            } else {
                printf("%c",style? 205:196);
            }
        } else if (i==dx) {
            printf("%c",style? 205:196);
        } else {
            printf(" ");
        }
    }
    if (i==1) {
        printf("%c",style? 187:191);
    } else if(i==dx){
        printf("%c",style? 188:217);
    } else{
        printf("%c",style? 186:179);
    }
    gotoxy(x1+i,y1);
}

}




void box (int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t style){ // Draws box
int8_t i, j;
int8_t dx = x2-x1+1;
int8_t dy = y2-y1;


if (x1 >= x2 || y1 >= y2){
    return;
}

gotoxy(x1,y1);

for (i=1; i<=dx; i++){
    if (i==1) {
        printf("%c",style? 201:218);
    } else if(i==dx){
        printf("%c",style? 200:192);
    } else{
        printf("%c",style? 186:179);
    }
    for ( j=1; j<=dy; j++){
        if (i==1){
            printf("%c",style? 205:196);
        } else if (i==dx) {
            printf("%c",style? 205:196);
        } else {
            printf(" ");
        }
    }
    if (i==1) {
        printf("%c",style? 187:191);
    } else if(i==dx){
        printf("%c",style? 188:217);
    } else{
        printf("%c",style? 186:179);
    }
    gotoxy(x1+i,y1);
}

}

void minibox (int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t style, uint8_t n){ // Draws small box with number
int8_t dx = x2-x1+1;
int8_t dy = y2-y1+1;

gotoxy(x1+dx/2-1,y1+dy/2-4);

int8_t vline;
int8_t hline;
int8_t vucorner;
int8_t vlcorner;
int8_t hucorner;
int8_t hlcorner;

if (style) {
    vline = 186;
    hline = 205;
    vucorner = 201;
    vlcorner = 200;
    hucorner = 187;
    hlcorner = 188;
} else {
    vline = 179;
    hline = 196;
    vucorner = 218;
    vlcorner = 192;
    hucorner = 191;
    hlcorner = 217;
}

printf("%c%c%c%c%c%c%c%c%c%c",vucorner, hline, hline, hline, hline, hline, hline, hline, hline, hucorner);
gotoxy(x1+dx/2,y1+dy/2-4);
printf("%cHits:",vline);
if (n<10){
    printf("%d  ", n);
} else if(n<100){
    printf("%d ", n);
} else{
    printf("%d", n);
}
printf("%c",vline);
gotoxy(x1+dx/2+1,y1+dy/2-4);
printf("%c%c%c%c%c%c%c%c%c%c",vlcorner, hline,hline, hline, hline, hline, hline, hline, hline, hlcorner);
}
