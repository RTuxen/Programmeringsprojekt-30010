#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"
#include "LUT.h"
#include "struct.h"
#include "gamePhysics.h"

void initBall (struct ball_t* ball, int32_t x, int32_t y, int32_t speed){
    ball->x = x << 14;
    ball-> y = y << 14;
    ball->speed = FIX14_MULT(speed << 14, 7000);
    ball->angle = 320;
//    ball->vec.x = FIX14_MULT(dx << 14, 5000);
//    ball->vec.y = FIX14_MULT(dy << 14, 5000);
}

void initPlayer(struct player_t * striker, uint16_t x, uint16_t y, uint8_t levelNum){
    striker->x = x;
    striker->y = y;
    striker->lives = 1;
    striker->level = levelNum;
    striker->points = 0;
}

void playGame(uint8_t levelNum){
    struct ball_t ball;
    struct player_t striker;
    struct level_t bane;
    static uint8_t buffer[512];
    int16_t slut=0;
    int32_t timerCount=0;

    //Initialisere LCD
    initBall(&ball,X2-7,Y2/2,0);//Initialisere bolden
//        initBall(ball,X2-7,Y2/2,0,0);
    initPlayer(&striker,X2-5,Y2/2, levelNum-1);//Initialisere strikeren
    initLevel(&ball,&striker,&bane);//Initialisere blokkene
    initDisplay(buffer);
    while(1){
            if (++timerCount==100000ul){
                updatePlayerPos(&striker);//Updatere strikeren
                slut = updateBallPos(&ball,&striker,&bane);//Updatere bolden og blokkene
                LCD_Printer(striker.level, striker.lives, striker.points, buffer);//Viser level, liv og point på LCD
                bossKey();

                fgcolor(15);
                gotoxy(30,10);
                printf("%4ld",ball.angle);

                if (slut){
                    chooseGameOver(striker.points, levelNum, buffer);//Stopper spillet, hvis liv = 0
                }
                timerCount=0;
            }
        }

}

void initLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level){
        clrscr();
        uint8_t i;

        level->lives = 0;

        for (i = 0; i < 32; i++) {
            level->blocks[i] = Level[striker->level][i];
            if (level->blocks[i].lives > 0) {
                level->lives += level->blocks[i].lives;
            }
        }
        drawWalls();
        drawBlockMap(level->blocks);
        drawball(ball);
        drawPlayer(striker);
}


void restartLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level){
        clrscr();

//        initBall(ball,X2-7,Y2/2,0,0);
        initBall(ball,X2-7,Y2/2,0);
        striker->x =X2-5;
        striker->y = Y2/2;


        drawWalls();
        drawBlockMap(level->blocks);
        drawball(ball);
        drawPlayer(striker);
}




uint16_t updateBallPos(struct ball_t * ball,struct player_t *striker, struct level_t *level){
        uint16_t playerhit = checkPlayerCollision(ball,striker);
        uint16_t wallhit = checkWallCollision(ball);
        checkBlockCollision(ball,level,striker);

        if (ball->angle < 0){
            ball->angle &= 511; // Makes angle positive
        }
        static int32_t oldx, oldy;
        oldx= ball->x;
        oldy = ball->y;


        if ( ball->speed == 0){
            ball->x = (striker->x-2) << 14;
            ball->y = (striker->y) << 14;
            if ( readJoyStickContinous() == 16){
                ball->speed = FIX14_MULT(1 << 14, 20000);
//                ball->vec.x = -FIX14_MULT(1 << 14, 10000);
//                ball->vec.y = FIX14_MULT(1 << 14, 10000);
            }

        }



        ball->x += FIX14_MULT(ball->speed,cosinus(ball->angle));
        ball->y += FIX14_MULT(ball->speed,sinus(ball->angle));


        // Makes sure ball doesn't exceed bounds with larger vectors
        if (wallhit == 1){
            if ( (ball->x >> 14) >= X2){
                ball->x = (X2-1) << 14;
            }
            if ( (ball->x >> 14) <= X1){
                ball->x = (X1+1) << 14;
            }
            if ( (ball->y >> 14) >= Y2){
                ball->y = (Y2-1) << 14;
            }
            if ( (ball->y >> 14) <= Y1){
                ball->y = (Y1+1) << 14;
            }
        } else if (wallhit ==2){ // Ball dead
            if ( striker->lives > 1){
                    striker->lives -=1;
                    restartLevel(ball,striker,level);
            } else{
                striker->lives -=1;
                return 1;
            }
        }

        if (playerhit){ // If ball hits player
            ball->x = (striker->x-1) << 14;
        }
        if ( oldx != ball->x || oldy != ball->y){
            gotoxy(oldx >> 14,oldy >> 14);
            printf(" ");
            drawball(ball);
        }
        return 0;
}

void updatePlayerPos(struct player_t *striker){
    fgcolor(1);
    static uint16_t oldPlayerx,oldPLayery;
    oldPlayerx = striker->x;
    oldPLayery = striker->y;

    if (readJoyStickContinous() == 4){ //Left
        if(oldPLayery-3 >= Y1+8){
            gotoxy(oldPlayerx,oldPLayery+7-2);
            printf("   ");
            moveCursor('D',15+3);
            printf("%c%c%c",219,219,219);
            striker->y -= 3;
        } else if(oldPLayery-1 >= Y1+8){
            gotoxy(oldPlayerx,oldPLayery+7-1);
            printf(" ");
            moveCursor('D',15+1);
            printf("%c",219);
            striker->y -=1;
        }
    } else if (readJoyStickContinous() == 8){ // Right
        if (oldPLayery+3 <= Y2-7){
            gotoxy(oldPlayerx,oldPLayery-7);
            printf("   ");
            moveCursor('C',15-3);
            printf("%c%c%c",219,219,219);
            striker->y += 3;
        } else if (oldPLayery+1 <= Y2-7){
            gotoxy(oldPlayerx,oldPLayery-7);
            printf(" ");
            moveCursor('C',15-1);
            printf("%c",219);
            striker->y +=1;
        }
    }


//    if( oldPlayerx != striker->x || oldPLayery != striker->y){
//        gotoxy(oldPlayerx,oldPLayery-7);
//        printf("               ");
//        drawPlayer(striker);
//    }
}

uint16_t checkWallCollision(struct ball_t * ball){
    int8_t i = 0;

    if ( (ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 <= X1){ // Top wall
        ball->angle = 256-ball->angle;
//        ball->vec.x = -ball->vec.x;
        i = 1;
    } else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >>14 >= X2){  // Die condition
        i = 2;
    }
    if ( (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= Y1 || (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= Y2 ){  // Left or right wall
        ball->angle = 512 - ball->angle;
//        ball->vec.y = -ball->vec.y;
        i= 1;
    }

    return i;
}

uint16_t checkPlayerCollision(struct ball_t * ball, struct player_t * striker){
    uint16_t hit = 0;

    // Player is divided into 5 sections
    if((ball->x >> 14) == striker->x || (ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == striker->x){
        if(((ball->y >> 14) >= striker->y-1 && (ball->y >> 14) <= striker->y+1)  || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y-1 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y-1)){
//Middle
            ball->angle = 256-ball->angle;
            hit = 1;

        } else if(((ball->y >> 14) >= striker->y-4 && (ball->y >> 14) <= striker->y-2) || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y-4 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y-2)){
//Left medium
//            if (ball->angle < 128){ //From Left
//                ball->angle = 256-(ball->angle*2)/3;
//            } else if (ball->angle > 384){ //from Right
//                ball->angle = 256-(ball->angle*3)/2;
//            }

            ball->angle = ball->angle < 128 ? 256-(ball->angle*2)/3 : 256-(ball->angle*3)/2;

            hit = 1;
        } else if(((ball->y >> 14) >= striker->y+2 && (ball->y >> 14) <= striker->y+4) || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y+2 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y+4)){
//Right medium
//            if (ball->angle < 128){ //From Left
//                ball->angle = 256-(ball->angle*3)/2;
//            } else if (ball->angle > 384){ //from Right
//                ball->angle = 256-(ball->angle*2)/3;
//            }
            ball->angle = ball->angle < 128 ? 256-(ball->angle*3)/2 : 256-(ball->angle*2)/3;

            hit = 1;
        } else if(((ball->y >> 14) >= striker->y-7 && (ball->y >> 14) <= striker->y-5) || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y-7 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y-5)){
//Left end
//            if (ball->angle < 128){ //From Left
//                ball->angle = 256-(ball->angle/3);
//            } else if (ball->angle > 384){ //from Right
//                ball->angle = 256-(ball->angle*3);
//            }
            ball->angle = ball->angle < 128 ? 256-ball->angle/3 : 256-ball->angle*3;

            hit = 1;
        } else if(((ball->y >> 14) >= striker->y+5 && (ball->y >> 14) <= striker->y+7) || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y+5 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y+7)){
//Right end
//            if (ball->angle > 0 && ball->angle < 128){ //From Left
//                ball->angle = 256-(ball->angle*3);
//                if (ball->angle > )
//            } else if (ball->angle > 384){ //from Right
//                ball->angle = 256-(ball->angle/3);
//            }
            ball->angle = ball->angle < 128 ? 256-ball->angle*3 : 256-ball->angle/3;

            hit = 1;
        }

        if (hit){
            ball->angle &= 511; // Sets angle within interval [0;511]
            if (ball->angle > 364){
                ball->angle = 364; // Corrects balls with wrong angle to the left
            } else if (ball->angle < 148){
                ball->angle = 148; // Corrects ball with wrong angle to the right
            }
        }

    }
    return hit;

}

uint16_t checkBlockCollision(struct ball_t* ball, struct level_t* level, struct player_t * striker) {
	uint8_t i;
	uint8_t hit;
	struct block_t * blocks = level->blocks;

	for (i = 0; i < 32; i++) {
		if (blocks[i].lives > 0) {
			hit = 0;

            // Check if ball hits from top or bottom
			if((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x || (ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x+1 ){
                    if((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >=blocks[i].y+1 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <=blocks[i].y+13){
                        ball->angle = 256-ball->angle;
                        hit = 1;
                    }
			} else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 == blocks[i].y){ // Top Left Corner
                if(ball->angle == 320){
                    ball->angle = 64;
                } else if(ball->angle > 320){
                    ball->angle = 512-ball->angle;
                } else if (ball->angle < 320){
                    ball->angle = 256-ball->angle;
                }
			} else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x+1 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 == blocks[i].y){ // Bottom Left Corner
                if(ball->angle == 448){
                    ball->angle = 192;
                } else if(ball->angle > 448){
                    ball->angle = 256-ball->angle;
                } else if (ball->angle < 448){
                    ball->angle = 512-ball->angle;
                }
			} else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 == blocks[i].y+14){ // Top Right COrner
                if(ball->angle == 64){
                    ball->angle = 320;
                } else if(ball->angle > 64){
                    ball->angle = 512-ball->angle;
                } else if (ball->angle < 64){
                    ball->angle = 256-ball->angle;
                }
			} else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x+1 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 == blocks[i].y+14){ // Bottom Right Corner
                if(ball->angle == 192){
                    ball->angle = 448;
                } else if(ball->angle > 192){
                    ball->angle = 256-ball->angle;
                } else if (ball->angle < 192){
                    ball->angle = 512-ball->angle;
                }
			}

			if (hit == 1) {

				blocks[i].lives--;
				drawBlock(blocks[i]);
				level->lives--;
				striker->points++;
			}

		}
	}
	return hit;
}

void bossKey(){
 int8_t hidden=0;
 int8_t joystikKey=readJoyStick();

 if(joystikKey==2){
        if (hidden==0){
        //funktion to minimize window
        printf("\e[2t");
        hidden = 1;
        }
        joystikKey=0;
        for (int i = 0 ; i < 10000 ; i++){}

            while(joystikKey!=2){
                joystikKey=readJoyStick();
            }
        printf("\e[1t"); //funktion to maximize window
        hidden = 0;

        }

}
