#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "graphics.h"

uint8_t strlens(char* text) { // Calculate the length of a string
	uint8_t length = 0;
	while(*text++ != '\0')
		length++;
	return length;
}


void window (int8_t x1, int8_t y1, int8_t x2, int8_t y2, char str[], int8_t style){ // Draws window with text in the middle
int8_t len = strlens(str);
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




void box (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, int8_t style){ // Draws box
int8_t i, j;
uint8_t dx = x2-x1+1;
uint8_t dy = y2-y1;

fgcolor(15);


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
fgcolor(15);

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

void stopWatchWindow(int8_t x1, int8_t y1, char str[], int8_t style) {
    fgcolor(15);
    int8_t x2 = x1+5;
    int8_t y2 = y1+30;

    window(x1, y1, x2, y2, str, style);
    gotoxy(x1+1,y1+2);
    printf("Time since start:  ");
    gotoxy(x1+2,y1+2);
    printf("Split time 1:      ");
    gotoxy(x1+3,y1+2);
    printf("Split time 2:      ");
}

void textReturn(int8_t len){
 char text[len];
 int8_t i = 1;
 int j;
    for (j = 0; j <= len; j++){
            text[j] = 0x00;
    }
 //   text[len] = '\0';
    text[0] = uart_getc();
    while(i<len-1 && text[i-1] != 0x0D){
    text[i]=uart_getc();
    i++;
    }
    text[i-1] = 0x00;

 //   gotoxy(16,30);
 //   printf("%s",text);
    compareString(text);
}


void compareString(char * text){ // Controls stopwatch using strings
char start[] = "start";
char split1[] = "split1";
char split2[] = "split2";
char reset[] = "reset";
char help[] = "help";
    if (strcmp(text,start) == 0){
        printf("\nstarting");
        stopWatchControl(16);

    } else if(strcmp(text,split1) == 0){
        gotoxy(12,30);
        stopWatchControl(4);
        getSavedCursor();
    } else if(strcmp(text,split2) == 0){
        gotoxy(13,30);
        stopWatchControl(8);
        getSavedCursor();
    } else if(strcmp(text,reset) == 0){
        printf("\nresetting");
        stopWatchControl(2);

    } else if(strcmp(text,help) == 0){
        userGuide();
    } else{
        commandList();
    }

}

void commandList(){
    printf("\nList of Proper Commands:\n1:start\n2:split1\n3:split2\n4:reset\n5:help");
}

void userGuide(){
    printf("\nType any command into Putty.");
 }

void drawWalls (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, int8_t style){ // Draws walls
    int8_t i, j;
    uint8_t dx = x2-x1+1;
    uint8_t dy = y2-y1;

    fgcolor(15);


    if (x1 >= x2 || y1 >= y2){
        return;
    }

    gotoxy(x1,y1);

    for (i=1; i<=dx; i++){
        if (i==1) {
            printf("%c",style? 201:218);
        } else{
            printf("%c",style? 186:179);
        }
        for ( j=1; j<=dy; j++){
            if (i==1){
                printf("%c",style? 205:196);
            } else {
                printf(" ");
            }
        }
        if (i==1) {
            printf("%c",style? 187:191);
        } else{
            printf("%c",style? 186:179);
        }
        gotoxy(x1+i,y1);
    }

}



void drawball(struct ball_t * ball){
    fgcolor(15);
    gotoxy(ball->x,ball->y);
    printf("o");
}

void drawPlayer(struct player_t *striker){
    fgcolor(1);
    gotoxy(striker->x,striker->y-3);
    printf("%c%c%c%c%c%c%c",111,205,205,205,205,205,111);

}
