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

void initPlayer(struct player_t * striker, uint8_t x, uint8_t y){
    striker->x = x;
    striker->y = y;
    striker->lifes = 3;
    striker->level = 0;
    striker->points = 0;
}

/*
void LoadLevel(struct ball_t ball, struct player_t striker){
        clrscr();

        initbold(&bold,12,10,1,1);
        initPlayer(&striker,37,58);
        initJoystick();

        drawWalls(X1,Y1,X2,Y2,1);
        drawball(&bold);
        drawPlayer(&striker);
        gotoxy(50,0);

}
*/

uint8_t updateBallPos(struct ball_t * ball,struct player_t *striker, int8_t x1 , int8_t y1,int8_t x2,int8_t y2){
        gotoxy(ball->x,ball->y);
        printf(" ");
        uint8_t playerhit = checkPlayerCollision(ball,striker);
        uint8_t wallhit = checkWallCollision(ball,x1,y1,x2,y2);

        ball->x += ball->vec.x;
        ball->y += ball->vec.y;


        // Makes sure ball doesn't exceed bounds with larger vectors
        if (wallhit == 1){
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
        } else if (wallhit ==2){
            return 1;
        }

        if (playerhit){ // If ball hits player
            ball->x = striker->x-1;
        }

        drawball(ball);
        return 0;
}

void updatePlayerPos(struct player_t *striker){
    uint8_t oldx = striker->x, oldy = striker->y;
    gotoxy(oldx,oldy-3);
    printf("       ");

    if (readJoyStick() == 4){ //Left
        if(oldy-3 >= 1+4){
            striker->y -= 3;
        } else if(oldy-1 >= 1+4){
            striker->y -=1;
        }
    } else if (readJoyStick() == 8){ // Right
        if (oldy+3 <= 117-4){
            striker->y += 3;
        } else if (oldy+1 <= 117-4){
            striker->y +=1;
        }
    }

    drawPlayer(striker);
}

int8_t checkWallCollision(struct ball_t * ball, int8_t x1 , int8_t y1 ,int8_t x2 ,int8_t y2){
    int8_t i = 0;

    if ( ball->x <= x1+1){
        ball->vec.x *= -1;
        i = 1;
    } else if (ball->x >= x2){
        i = 2;
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

uint8_t checkPlayerCollision(struct ball_t * ball, struct player_t * striker){
    uint8_t hit = 0;

    // Player is divided into 5 sections
    if(ball->x == striker->x || ball->vec.x+ball->x == striker->x){
        if(ball->y == striker->y){ // Middle
            ball->vec.x *= -1;
            hit = 1;
        } else if(ball->y == striker->y-1 || ball->y == striker->y-2 ||
                  ball->y+ball->vec.y == striker->y-1 || ball->y+ball->vec.y == striker->y-2){ // Left Medium
            ball->vec.x *= -1;
            hit = 1;
        } else if(ball->y == striker->y+1 || ball->y == striker->y+2 ||
                  ball->y+ball->vec.y == striker->y+1 || ball->y+ball->vec.y == striker->y+2){ // Right Medium
            ball->vec.x *= -1;
            hit = 1;
        } else if(ball->y == striker->y-3 ||ball->y+ball->vec.y == striker->y-3){ // Left End
            ball->vec.x *= -1;
            hit = 1;
        } else if(ball->y == striker->y+3 || ball->y+ball->vec.y == striker->y+3){ // Right End
            ball->vec.x *= -1;
            hit = 1;
        }
    }
    return hit;

}

