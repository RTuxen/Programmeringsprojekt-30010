#include "gamePhysics.h"

int32_t ballMoveX(struct ball_t * ball){ // Moves ball one step in X direction
    return ball->x + FIX14_MULT(ball->speed,cosinus(ball->angle));
}

int32_t ballMoveY(struct ball_t * ball){ // Moves ball one step in X direction
    return ball->y+ FIX14_MULT(ball->speed,sinus(ball->angle));
}

void updateFallingObject(struct fallingObject_t *fallObject, struct player_t * striker, struct game_state_t* gs){

    if(fallObject->y <= striker->y+7 && fallObject->x+1 == striker->x && fallObject->y >= striker->y-7){
        gotoxy(fallObject->x, fallObject->y);
        printf(" ");

        if(fallObject->type==1){
            gs->lives--;
        }else if (fallObject->type==2){
            gs->lives++;
        }else if (fallObject->type==3){
            gs->mirror = !gs->startmirror;
            gs->mirroruptime = tid.seconds;
        }else if (fallObject->type==4){
            gs->randomAnglePowerup = 1;
            gs->randomAnglePoweruptime = tid.seconds;
        }
        fallObject->type=0;
    } else if (fallObject->x < X2 && fallObject->type){// If no collision, keep on moving
        gotoxy(fallObject->x, fallObject->y);
        printf(" ");
        fallObject->x++;
        printfallObject(fallObject);
    } else if (fallObject->x >= X2){
        gotoxy(fallObject->x, fallObject->y);
        printf(" ");
        fallObject->type = 0;
    }
}

void updateFallingObject2Players(struct fallingObject_t *fallObject, struct player_t * striker, struct player_t * striker2, struct game_state_t* gs){

    if((fallObject->y <= striker->y+7 && fallObject->x+1 == striker->x && fallObject->y >= striker->y-7) || (fallObject->y <= striker2->y+7 && fallObject->x+1 == striker2->x && fallObject->y >= striker2->y-7)){
        gotoxy(fallObject->x, fallObject->y);
        printf(" ");

        if(fallObject->type==1){
            gs->lives--;
        }else if (fallObject->type==2){
            gs->lives++;
        }else if (fallObject->type==3){
            gs->mirror = !gs->startmirror;
            gs->mirroruptime = tid.seconds;
        }else if (fallObject->type==4){
            gs->randomAnglePowerup = 1;
            gs->randomAnglePoweruptime = tid.seconds;
        }
        fallObject->type=0;
    } else if (fallObject->x < X2 && fallObject->type){// If no collision, keep on moving
        gotoxy(fallObject->x, fallObject->y);
        printf(" ");
        fallObject->x++;
        printfallObject(fallObject);
    } else if (fallObject->x >= X2){
        gotoxy(fallObject->x, fallObject->y);
        printf(" ");
        fallObject->type = 0;
    }
}

void updateBallPos(struct ball_t * ball,struct player_t *striker, struct level_t *level, struct game_state_t * gs,struct fallingObjectsType_t * fallObject_ptr){
        checkPlayerCollision(ball,striker,gs);
        uint16_t bottomHit = checkWallCollision(ball,gs);
        checkBlockCollision(ball, level, gs, fallObject_ptr);

        static int32_t oldx, oldy;
        oldx= ball->x;
        oldy = ball->y;


        if ( ball->speed == 0){ // If game hasen't started
            ball->x = (striker->x-2) << 14;
            ball->y = (striker->y) << 14;
            if ( readJoyStickContinous() == 16){
                ball->speed = FIX14_MULT(1 << 14, 8000);
            }

        }


        ball->x = ballMoveX(ball);
        ball->y = ballMoveY(ball);



        // If ball is dead
        if (bottomHit){
                gs->lives--;
        }


        if ( oldx != ball->x || oldy != ball->y){ // Only draws if there is a new ball position
            gotoxy(oldx >> 14,oldy >> 14);
            printf(" ");
            drawball(ball);
        }
}

void updateBallPos2Players(struct ball_t * ball,struct player_t *striker,struct player_t * striker2, struct level_t *level, struct game_state_t * gs, struct fallingObjectsType_t * fallObject_ptr){
        uint16_t bottomHit;
        setFreq(0); // Kills sound

        checkPlayerCollision(ball,striker,gs);
        checkPlayerCollision(ball,striker2,gs);
        bottomHit = checkWallCollision(ball,gs);
        checkBlockCollision(ball, level, gs,fallObject_ptr);

        static int32_t oldx, oldy;
        oldx= ball->x;
        oldy = ball->y;


        if ( ball->speed == 0){ // If game hasen't started
            ball->x = (striker->x-2) << 14;
            ball->y = (striker->y) << 14;
            if ( readJoyStickContinous() == 16){
                ball->speed = FIX14_MULT(1 << 14, 8000);
            }

        }


        ball->x = ballMoveX(ball);
        ball->y = ballMoveY(ball);



        // If ball is dead
        if (bottomHit){
                gs->lives -=1;
        }


        if ( oldx != ball->x || oldy != ball->y){ // Only draws if there is a new ball position
            gotoxy(oldx >> 14,oldy >> 14);
            printf(" ");
            drawball(ball);
        }
}

uint16_t checkWallCollision(struct ball_t * ball, struct game_state_t *gs){
    int8_t bottomHit = 0;

    if ( ballMoveX(ball) >> 14 <= X1){ // Top wall
        setFreq(500); // Hit Sound
        ball->angle = 256-ball->angle;
        ball->x = (X1+1) << 14;
        if (gs->randomAnglePowerup){
        ball->angle = (tid.randomAngle &=0xD4)+404; // Random angle between 404 and 104
        }
    } else if (ballMoveX(ball) >>14 >= X2){  // Die condition
        bottomHit = 1;
    }
    if ( ballMoveY(ball) >> 14 <= Y1){  // Left  Wall
        setFreq(500); // Hit Sound
        ball->angle = 512 - ball->angle;
        ball->y = (Y1+1) << 14;
        if (gs->randomAnglePowerup){
        ball->angle = (tid.randomAngle &=0xD4)+20; // Random angle between 20 and 232
        }
    } else if (ballMoveY(ball) >> 14 >= Y2){ // Right wall
        setFreq(500); // Hit Sound
        ball->angle = 512 - ball->angle;
        ball->y = (Y2-1) << 14;
        if (gs->randomAnglePowerup){
        ball->angle = (tid.randomAngle &=0xD4)+276; // Random angle between 276 and 448
        }
    }

    if (ball->angle < 0){
            ball->angle &= 511; // Makes angle positive
        }

    return bottomHit;
}

void checkPlayerCollision(struct ball_t * ball, struct player_t * striker, struct game_state_t * gs){
    uint16_t hit = 0;
    setFreq(0);

    // Striker is divided into 5 sections

    if(ballMoveX(ball) >> 14 == striker->x){
        if(((ball->y >> 14) >= striker->y-1 && (ball->y >> 14) <= striker->y+1)){ //Middle

            ball->angle = 256-ball->angle;
            hit = 1;

        } else if(((ball->y >> 14) >= striker->y-4 && (ball->y >> 14) <= striker->y-2)){ //Left medium

            ball->angle = ball->angle < 128 ? 256-(ball->angle*2)/3 : 256+((ball->angle-384)*3)/2;
            hit = 1;

        } else if(((ball->y >> 14) >= striker->y+2 && (ball->y >> 14) <= striker->y+4)){ //Right medium

            ball->angle = ball->angle < 128 ? 256-(ball->angle*3)/2 : 256+((ball->angle-384)*2)/3;
            hit = 1;

        } else if(((ball->y >> 14) >= striker->y-7 && (ball->y >> 14) <= striker->y-5)){ //Left end

            if (ball->angle < 128){ // Ball hits from left
                ball->angle = 256-ball->angle/3;
            } else if( ball->angle > 384){ // Ball hits from right
                ball->angle = 256+(ball->angle-384)*3;
                if (ball->angle > 512){
                    ball->angle = -ball->angle;
                }
            }
            hit = 1;

        } else if(((ball->y >> 14) >= striker->y+5 && (ball->y >> 14) <= striker->y+7)){ //Right end

            if (ball->angle < 128){ // Ball hits from left
                ball->angle = 256-ball->angle*3;
                if (ball->angle < 0){
                    ball->angle = -ball->angle;
                }
            } else if( ball->angle > 384){ // Ball hits from right
                ball->angle = 256+(ball->angle-384)/3;
            }
            hit = 1;
        }

        if (hit){
            setFreq(1000);
            ball->angle &= 511; // Sets angle within interval [0;511]
            ball->x = (striker->x-1) << 14;
            if (ball->angle > 364){
                ball->angle = 364; // Corrects balls with wrong angle to the left
            } else if (ball->angle < 148){
                ball->angle = 148; // Corrects ball with wrong angle to the right
            }
            if (gs->randomAnglePowerup){ // If Randomangle powerup is active
            ball->angle = (tid.randomAngle &=0xD4)+148; // Random angle between 148 and 360
            }
        }



    }

}

void checkBlockCollision(struct ball_t* ball, struct level_t* level, struct game_state_t * gs, struct fallingObjectsType_t *fallObject_ptr) {
	uint8_t i;
	static uint8_t hit;
	struct block_t * blocks = level->blocks;
	hit = 0;

	for (i = 0; i < 32; i++) { // Checks all blocks
		if (blocks[i].lives > 0) {
			hit = 0;

            // Blocks are divided into 5 areas: 4 corners and one top-bottom surface

            if(ballMoveX(ball) >> 14 == blocks[i].x || ballMoveX(ball) >> 14 == blocks[i].x+1 ){ // Check if ball hits from top or bottom
                if((ballMoveY(ball) >> 14 >= blocks[i].y+1 && ballMoveY(ball) >> 14 <= blocks[i].y+13) ){ // Top and bottom sides
                       ball->angle = 256-ball->angle;
                       hit = 1;
                   } else if( (ballMoveX(ball) >> 14 == blocks[i].x && ballMoveY(ball) >> 14 ==blocks[i].y)  ){ // Top Left Corner
                       hit = 1;
                       if(ball->angle == 64){ // Checks angle and determines exit angle
                           ball->angle = 64;
                       } else if(ball->angle < 64 || ball->angle > 384){
                            ball->angle = -ball->angle;
                       } else if (ball->angle > 64){
                           ball->angle = 256-ball->angle;
                       }
                   } else if( (ballMoveX(ball) >> 14 == blocks[i].x+1 && ballMoveY(ball) >> 14 ==blocks[i].y) ){ // Bottom Left Corner
                       hit = 1;
                       if(ball->angle == 192){ // Checks angle and determines exit angle
                           ball->angle = 448;
                       } else if(ball->angle > 192){
                           ball->angle = 256-ball->angle;
                       } else if (ball->angle < 192){
                           ball->angle = -ball->angle;
                       }
                   } else if( (ballMoveX(ball) >> 14 == blocks[i].x && ballMoveY(ball) >> 14 ==blocks[i].y+14) ){ // Top right Corner
                       hit = 1;
                       if(ball->angle == 448){ // Checks angle and determines exit angle
                           ball->angle = 192;
                       } else if(ball->angle > 448 || ball->angle < 128){
                           ball->angle = 256-ball->angle;
                       } else if (ball->angle < 448){
                           ball->angle = -ball->angle;
                       }
                   } else if((ballMoveX(ball) >> 14 == blocks[i].x+1 && ballMoveY(ball) >> 14 ==blocks[i].y+14) ){ // Bottom right Corner
                       hit = 1;
                       if(ball->angle == 320){ // Checks angle and determines exit angle
                           ball->angle = 64;
                       } else if(ball->angle > 320){
                           ball->angle = -ball->angle;
                       } else if (ball->angle < 320){
                           ball->angle = 256-ball->angle;
                       }
                }
			}
			if (hit == 1) { // If the ball hits a block
                setFreq(500); // Hit Sound
				blocks[i].lives--;
				drawBlock(blocks[i]);
				level->lives--;
				gs->points++;
				if (blocks[i].lives==0 && blocks[i].fallingObject>0){ // If block contains a Power Up
                    fallObject_ptr->fallingObjectArray [fallObject_ptr->numberOfObjects].type = blocks[i].fallingObject;
                    fallObject_ptr->fallingObjectArray [fallObject_ptr->numberOfObjects].x=blocks[i].x;
                    fallObject_ptr->fallingObjectArray [fallObject_ptr->numberOfObjects].y=blocks[i].y;
                    fallObject_ptr->numberOfObjects++;
                }
			}
		}
	}
	if (ball->angle < 0){
        ball->angle &= 511; // Makes angle positive
    }
}



