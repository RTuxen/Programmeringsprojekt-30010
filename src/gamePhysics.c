#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"
#include "LUT.h"
#include "struct.h"
#include "gamePhysics.h"

void initbold (struct ball_t* ball, int32_t x, int32_t y, int32_t dx, int32_t dy){
ball->x = x;
ball-> y = y;
ball->vec.x=dx;
ball->vec.y=dy;


}

void update(struct ball_t * ball,int8_t x1 , int8_t y1,int8_t x2,int8_t y2){
    gotoxy(ball->x,ball->y);
    printf(" ");


        ball->x += ball->vec.x;
        ball->y += ball->vec.y;


        // Makes sure ball doesn't exceed bounds with larger vectors
        if ( ball->x >= x2){
            ball->x = x2-1;
        }
        if ( ball->x <= x1){
            ball->x = x1+1;
        }
        if ( ball->y >= y2){
            ball->y = y2-1;
        }
        if ( ball->y <= y1){
            ball->y = y1+1;
        }

}

void drawball(struct ball_t * ball){
    gotoxy(ball->x,ball->y);
    printf("o");
}

int8_t checkWallCollision(struct ball_t * ball, int8_t x1 , int8_t y1 ,int8_t x2 ,int8_t y2){
    int8_t i = 0;

    if ( ball->x <= x1+1 || ball->x >= x2-1 ){
            ball->vec.x *= -1;
            i = 1;
    }
    if ( ball->y <= y1+1 || ball->y >= y2-1 ){
            ball->vec.y *= -1;
            i= 1;
    }


/*
    // Check for collision with top wall
    if (ball->x <= x1+1 && ball->vec.y > 0){ // if ball comes from left
        rotat(&ball->vec,-128);
        i = 1;
    } else if (ball->x <= x1+1 && ball->vec.y < 0){ // if ball comes from right
        rotat(&ball->vec,128);
        i = 1;
    }

    // Check for collision with bottom wall
    else if (ball->x >= x2-1 && ball->vec.y > 0){ // if ball comes from left
        rotat(&ball->vec,128);
        i = 1;
    } else if (ball->x >= x2-1 && ball->vec.y < 0){ // if ball comes from right
        rotat(&ball->vec,-128);
        i = 1;
    }


    // Check for collision with right wall
    if (ball->y <= y1+1 && ball->vec.x > 0){ // if ball comes from above
        rotat(&ball->vec,128);
        i = 1;
    } else if (ball->y <= y1+1 && ball->vec.x < 0){ // if ball comes from bellow
        rotat(&ball->vec,-128);
        i = 1;
    }

    // Check for collision with left wall
    else if (ball->y >= y2-1 && ball->vec.x > 0){ // if ball comes from above
        rotat(&ball->vec,-128);
        i = 1;
    } else if (ball->y >= y2-1 && ball->vec.x < 0){ // if ball comes from bellow
        rotat(&ball->vec,128);
        i = 1;
    }
*/
    return i;
}
