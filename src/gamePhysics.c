#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"
#include "LUT.h"
#include "struct.h"
#include "gamePhysics.h"

void update(struct ball_t * ball, int8_t hit,int8_t x1 , int8_t y1,int8_t x2,int8_t y2){
    gotoxy(ball->x,ball->y);
    printf(" ");

        ball->x += ball->dx;
        ball->y += ball->dy;

    if (ball->x <= x1) {
            ball->x += (x1-ball->x-ball->dx)-ball->dx -2;
    }
     if (ball->x >= x2) {
            ball->x += (x2-ball->x-ball->dx)-ball->dx -1;
    }
}

void drawball(struct ball_t * ball){
    gotoxy(ball->x,ball->y);
    printf("o");
}

int8_t checkEdge(struct ball_t * ball, int8_t x1 , int8_t y1,int8_t x2,int8_t y2){

    if ( ball->x <= x1+1 || ball->x >= x2-1 ){
            ball->dx *=-1;
            return 1;
    }
    if ( ball->y <= y1+1 || ball->y >= y2 ){
            ball->dy *=-1;
            return 1;
    }
    return 0;
}
