#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"
#include "LUT.h"
#include "struct.h"
#include "gamePhysics.h"

void initbold (struct ball_t* ball, int32_t x, int32_t y, int32_t dx, int32_t dy){
    ball->x = x << 14;
    ball-> y = y << 14;
    ball->vec.x = FIX14_MULT(dx << 14, 5000);
    ball->vec.y = FIX14_MULT(dy << 14, 5000);
}

void initPlayer(struct player_t * striker, uint16_t x, uint16_t y){
    striker->x = x;
    striker->y = y;
    striker->lifes = 3;
    striker->level = 0;
    striker->points = 0;
}


void initLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level){
        clrscr();
        uint8_t i;

        initbold(ball,X2-7,Y2/2,0,0);
        initPlayer(striker,X2-5,Y2/2);
        initJoystick();
        level->lifes = 0;

        for (i = 0; i < 32; i++) {
            level->blocks[i] = Level1[i];
            if (level->blocks[i].lifes > 0) {
                level->lifes += level->blocks[i].lifes;
            }
        }
        drawWalls();
        drawBlockMap(level->blocks);
        drawball(ball);
        drawPlayer(striker);
}




uint16_t updateBallPos(struct ball_t * ball,struct player_t *striker, struct level_t *level){
        gotoxy(ball->x >> 14,ball->y >> 14);
        printf(" ");
        uint16_t playerhit = checkPlayerCollision(ball,striker);
        uint16_t wallhit = checkWallCollision(ball);
        checkBlockCollision(ball,level);


        if ( ball->vec.x == 0 && ball->vec.y == 0){
            ball->x = (striker->x-2) << 14;
            ball->y = (striker->y) << 14;
            if ( readJoyStickContinous() == 16){
                ball->vec.x = -FIX14_MULT(1 << 14, 5000);
                ball->vec.y = FIX14_MULT(1 << 14, 5000);
            }

        }


        ball->x += ball->vec.x;
        ball->y += ball->vec.y;


        // Makes sure ball doesn't exceed bounds with larger vectors
        if (wallhit == 1){
            if ( (ball->x >> 14) >= X2){
                ball->x = X2-1;
            }
            if ( (ball->x >> 14) <= X1){
                ball->x = X1+1;
            }
            if ( (ball->y >> 14) >= Y2){
                ball->y = Y2-1;
            }
            if ( (ball->y >> 14) <= Y1){
                ball->y = Y1+1;
            }
        } else if (wallhit ==2){ // Ball dead
            return 1;
        }

        if (playerhit){ // If ball hits player
            ball->x = (striker->x-1) << 14;
        }

        drawball(ball);
        return 0;
}

void updatePlayerPos(struct player_t *striker){
    uint16_t oldx = striker->x, oldy = striker->y;
    gotoxy(oldx,oldy-7);
    printf("               ");

    if (readJoyStickContinous() == 4){ //Left
        if(oldy-1 >= Y1+8){
            striker->y -= 1;
        } else if(oldy-1 >= Y1+8){
            striker->y -=1;
        }
    } else if (readJoyStickContinous() == 8){ // Right
        if (oldy+1 <= Y2-7){
            striker->y += 1;
        } else if (oldy+1 <= Y2-7){
            striker->y +=1;
        }
    }

    drawPlayer(striker);
}

uint16_t checkWallCollision(struct ball_t * ball){
    int8_t i = 0;

    if ( (ball->x+ball->vec.x) >> 14 <= X1){ // Top wall
        ball->vec.x = -ball->vec.x;
        i = 1;
    } else if ((ball->x+ball->vec.x) >>14 >= X2){  // Die condition
        i = 2;
    }
    if ( (ball->y+ball->vec.y) >> 14 <= Y1 || (ball->y+ball->vec.y) >> 14 >= Y2 ){  // Left or right wall
        ball->vec.y = -ball->vec.y;
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

uint16_t checkPlayerCollision(struct ball_t * ball, struct player_t * striker){
    uint16_t hit = 0;

    // Player is divided into 5 sections
    if((ball->x >> 14) == striker->x || ball->vec.x+(ball->x >> 14) == striker->x){ // Central
        if(((ball->y >> 14) >= striker->y-1 && (ball->y >> 14) <= striker->y+1)  || ((ball->y >> 14)+ball->vec.y >= striker->y-1 && (ball->y >> 14)+ball->vec.y <= striker->y-1)){ // Middle
            ball->vec.x = -ball->vec.x;
            hit = 1;
        } else if(((ball->y >> 14) >= striker->y-4 && (ball->y >> 14) <= striker->y-2) || ((ball->y >> 14)+ball->vec.y >= striker->y-4 && (ball->y >> 14)+ball->vec.y <= striker->y-2)){ // Left Medium
            ball->vec.x = -ball->vec.x;
            hit = 1;
        } else if(((ball->y >> 14) >= striker->y+2 && (ball->y >> 14) <= striker->y+4) || ((ball->y >> 14)+ball->vec.y >= striker->y+2 && (ball->y >> 14)+ball->vec.y <= striker->y+4)){ // Right Medium
            ball->vec.x = -ball->vec.x;
            hit = 1;
        } else if(((ball->y >> 14) >= striker->y-7 && (ball->y >> 14) <= striker->y-5) || ((ball->y >> 14)+ball->vec.y >= striker->y-7 && (ball->y >> 14)+ball->vec.y <= striker->y-5)){ // Left End
            ball->vec.x = -ball->vec.x;
            hit = 1;
        } else if(((ball->y >> 14) >= striker->y+5 && (ball->y >> 14) <= striker->y+7) || ((ball->y >> 14)+ball->vec.y >= striker->y+5 && (ball->y >> 14)+ball->vec.y <= striker->y+7)){ // Right End
            ball->vec.x = -ball->vec.x;
            hit = 1;
        }
    }
    return hit;

}

uint16_t checkBlockCollision(struct ball_t* ball, struct level_t* level) {
	uint8_t i;
	uint8_t hit;
	struct block_t * blocks = level->blocks;

	for (i = 0; i < 32; i++) {
		if (blocks[i].lifes > 0) {
			hit = 0;

            // Check if ball hits from top or bottom
			if((ball->x+ball->vec.x) >> 14 == blocks[i].x || (ball->x+ball->vec.x) >> 14 == blocks[i].x+1 ){
                    if((ball->y+ball->vec.y) >> 14 >=blocks[i].y && (ball->y+ball->vec.y) >> 14 <=blocks[i].y+14){
                        ball->vec.x = -ball->vec.x;
                        hit = 1;
                    }
			}

			if (hit == 1) {

				blocks[i].lifes--;
				drawBlock(blocks[i]);
				level->lifes--;

			}

		}
	}
	return hit;
}

