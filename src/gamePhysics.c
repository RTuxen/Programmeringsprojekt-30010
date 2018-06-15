#include "gamePhysics.h"

void initBall (struct ball_t* ball, int32_t x, int32_t y, int32_t speed){
    ball->x = x << 14;
    ball-> y = y << 14;
    ball->speed = FIX14_MULT(speed << 14, 7000);
    ball->angle = (tid.randomAngle &=0xD4)+148; // Random angle between 148 and 360



}

void initPlayer(struct player_t * striker, uint16_t x, uint16_t y){
    striker->x = x;
    striker->y = y;
}

void initGameState(struct game_state_t* gs){
    gs->speed = 1;
    gs->startmirror = 0;
    gs->mirror = 0;
    readFlash(gs);
    gs->points = 0;
    gs->lives = 0;
    gs->startlevel = 0;
    gs->currentlevel = 0;
    gs->players = 1;
}

void playGame(struct game_state_t* gs){

    struct ball_t ball;
    struct player_t striker;
    struct level_t level;
    struct fallingObject_t fallObject;

    int8_t delay = 0;
    int8_t oldlives, i, j;

    struct fallingObjectsType_t fallingObjects;
    fallingObjects.numberOfObjects = 0;

    setTimer(gs->speed, gs->currentlevel); // Sets game speed
    gs->mirror = gs->startmirror;//Sets mirror to the chosen option
    if (gs->currentlevel == gs->startlevel){
        gs->lives = 1; //Sætter spillerens liv
    }
    oldlives = gs->lives;// Sets oldlives to startlives at the start of the game
    initLED();

    if (gs->players == 2){

        struct ball_t ball2;
        struct player_t striker2;

        initBall(&ball,X2-7,Y1+50,0); //Initialiserer bold1
        initBall(&ball2,X2-5,Y2-50,0);//Initialiserer bold2
        initPlayer(&striker,X2-5,Y1+50); //Initialiserer striker1
        initPlayer(&striker2,X2-5,Y2-50); //Initialiserer striker1
        initLevel2Players(&ball,&ball2,&striker,&striker2,&level, gs); //Initialiserer blokkene
        initDisplay(gs->buffer);

        while(1){
            if (get_game_flag()){
                if(delay++ > 3){
                    delay = 0;
                    j = fallingObjects.numberOfObjects;
                    for (i = 0; i < j; i++){
                        if (fallingObjects.fallingObjectArray[i].type != 0){

                            fallObject=fallingObjects.fallingObjectArray[i];
                            updateFallingObject(&fallObject,&striker,gs);// check if collision with player
                            printfallObject(&fallObject);// Prints the powerup
                            fallingObjects.fallingObjectArray[i]=fallObject;
                        }

                    }

                }

                // Checks if poweruptime has been reached
                if (tid.seconds >= (gs->mirroruptime+5)){
                    gs->mirror = gs->startmirror;
                }
                if (tid.seconds >= gs->randomAnglePoweruptime+25){
                    gs->randomAnglePowerup = 0;
                }

                updatePlayerPosPotentiometer(&striker,0);// Updates striker
                updatePlayerPosPotentiometer(&striker2,1);// Updates striker2
                updateBallPos2Players(&ball,&striker,&striker2,&level, gs,&fallingObjects);// Updates the ball and the blocks
                updateBallPos2Players(&ball2,&striker2,&striker,&level, gs,&fallingObjects);// Updates the ball and the blocks
                LCD_Printer(gs);// Shows level, lives and points on the LCD
                bossKey();
                setLed(gs);

                if (!gs->lives){// Checks for gameover
                    chooseGameOver(gs);
                } else if (gs->lives == oldlives-1){// Checks if any lives have been lost - Can happen through a powerup or a lost ball
                    gs->mirror = gs->startmirror;
                    restartLevel(&ball,&striker,&level);
                } else if (!(level.lives) && gs->currentlevel == 5){
                    chooseGameWon(gs);
                } else if (!(level.lives)){
                    gs->currentlevel++;
                    playGame(gs);
                }
                oldlives = gs->lives;// Sets oldlives to the new amount of lives
            }
        }

    } else {
        initBall(&ball,X2-7,Y2/2,0); //Initialiserer bolden
        initPlayer(&striker,X2-5,Y2/2); //Initialiserer strikeren
        initLevel(&ball,&striker,&level, gs); //Initialiserer blokkene
        initDisplay(gs->buffer);

        while(1){//Spil-loopet startes
            if (get_game_flag()){
                if(delay++ > 3){
                    delay = 0;
                    j=fallingObjects.numberOfObjects;
                    for (i=0; i<j;i++){
                        if (fallingObjects.fallingObjectArray[i].type!=0){
                            fallObject=fallingObjects.fallingObjectArray[i];

                            updateFallingObject(&fallObject, &striker, gs);// check if collision with player
                            printfallObject(&fallObject);
                            fallingObjects.fallingObjectArray[i]=fallObject;
                        }
                    }
                }
                // Checks if poweruptime has been reached
                if (tid.seconds >= (gs->mirroruptime+5) && gs->mirror != gs->startmirror){
                    gs->mirror = gs->startmirror;
                }
                if (tid.seconds >= gs->randomAnglePoweruptime+25 && gs->randomAnglePowerup){
                    gs->randomAnglePowerup = 0;
                }
                updatePlayerPos(&striker,gs);// Updates the striker
                updateBallPos(&ball,&striker,&level, gs,&fallingObjects);// Updates the ball and the blocks
                LCD_Printer(gs);// Shows level, lives and points on the LCD
                bossKey();
                setLed(gs);// Sets the RGB LED to the appropriate color

                if (gs->lives < 1){// Checks for gameover
                    turnOffLED();
                    chooseGameOver(gs);
                } else if (gs->lives < oldlives){// Checks if any lives have been lost - Can happen through a powerup or a lost ball
                    gs->mirror = gs->startmirror;
                    restartLevel(&ball,&striker,&level);
                } else if (!(level.lives) && gs->currentlevel == 5){
                    chooseGameWon(gs);
                } else if (!(level.lives)){
                    gs->currentlevel++;
                    playGame(gs);
                }

                oldlives = gs->lives;// Sets oldlives to the new amount of lives
            }
        }
    }
}

void initLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level, struct game_state_t* gs){
        clrscr();
        uint8_t i;

        level->lives = 0;

        for (i = 0; i < 32; i++) {
            level->blocks[i] = Level[gs->currentlevel-1][i];
            if (level->blocks[i].lives > 0) {
                level->lives += level->blocks[i].lives;
            }
        }
        drawWalls();
        drawBlockMap(level->blocks);
        drawball(ball);
        drawPlayer(striker);
}

void initLevel2Players(struct ball_t *ball,struct ball_t * ball2, struct player_t *striker, struct player_t *striker2, struct level_t *level, struct game_state_t* gs){
        clrscr();
        uint8_t i;

        level->lives = 0;

        for (i = 0; i < 32; i++) {
            level->blocks[i] = Level[gs->currentlevel-1][i];
            if (level->blocks[i].lives > 0) {
                level->lives += level->blocks[i].lives;
            }
        }
        drawWalls();
        drawBlockMap(level->blocks);
        drawball(ball);
        drawball(ball2);
        drawPlayer(striker);
        drawPlayer(striker2);
}


void restartLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level){
        clrscr();

        initBall(ball,X2-7,Y2/2,0);
        striker->x =X2-5;
        striker->y = Y2/2;


        drawWalls();
        drawBlockMap(level->blocks);
        drawball(ball);
        drawPlayer(striker);
}

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
            printf("Dead");
            gs->lives--;
        }else if (fallObject->type==2){
            printf("wuhuu");
            gs->lives++;
        }else if (fallObject->type==3){
            gs->mirror = !gs->startmirror;
            gs->mirroruptime = tid.seconds;
            printf("Mirror-Mode!");
        }else if (fallObject->type==4){
            gs->randomAnglePowerup = 1;
            gs->randomAnglePoweruptime = tid.seconds;
            printf("Random angle");
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

void updatePlayerPosPotentiometer(struct player_t * striker, int8_t playerNo){
    fgcolor(15);
    static uint16_t oldPlayerx, oldPLayery;
    oldPlayerx = striker->x;
    oldPLayery = striker->y;

    if(playerNo){ // Right Player
        if(readADC_pa1() < 2700){ // Left
            if(oldPLayery-1 >= 120+8){
                gotoxy(oldPlayerx,oldPLayery+7);
                printf(" ");
                moveCursor('D',15+1);
                printf("%c",219);
                striker->y -=1;
            }
        } else if (readADC_pa1() > 3300){ //Right
            if (oldPLayery+1 <= Y2-7){
                gotoxy(oldPlayerx,oldPLayery-7);
                printf(" ");
                moveCursor('C',15-1);
                printf("%c",219);
                striker->y +=1;
            }
        }

    } else{ // Left player
        if(readADC_pa0() < 2700){ // Left
            if(oldPLayery-1 >= Y1+8){
                gotoxy(oldPlayerx,oldPLayery+7);
                printf(" ");
                moveCursor('D',15+1);
                printf("%c",219);
                striker->y -=1;
            }
        } else if (readADC_pa0() > 3300){ //Right
            if (oldPLayery+1 <= 120-7){
                gotoxy(oldPlayerx,oldPLayery-7);
                printf(" ");
                moveCursor('C',15-1);
                printf("%c",219);
                striker->y +=1;
            }
        }
    }
}

void updatePlayerPos(struct player_t *striker, struct game_state_t* gs){
    fgcolor(15);
    static uint16_t oldPlayerx,oldPLayery;
    oldPlayerx = striker->x;
    oldPLayery = striker->y;


if (gs->mirror) {
        if (readJoyStickContinous() == 8)  //Left
    {

        if(oldPLayery-1 >= Y1+8)
        {
            gotoxy(oldPlayerx,oldPLayery+7);
            printf(" ");
            moveCursor('D',15+1);
            printf("%c",219);
            striker->y--;
        }
    }
    else if (readJoyStickContinous() == 4)    // Right
    {

        if (oldPLayery+1 <= Y2-7)
        {
            gotoxy(oldPlayerx,oldPLayery-7);
            printf(" ");
            moveCursor('C',15-1);
            printf("%c",219);
            striker->y++;
        }
    }
} else {
        if (readJoyStickContinous() == 4)  //Left
    {

        if(oldPLayery-1 >= Y1+8)
        {
            gotoxy(oldPlayerx,oldPLayery+7);
            printf(" ");
            moveCursor('D',15+1);
            printf("%c",219);
            striker->y--;
        }
    }
    else if (readJoyStickContinous() == 8)    // Right
    {

        if (oldPLayery+1 <= Y2-7)
        {
            gotoxy(oldPlayerx,oldPLayery-7);
            printf(" ");
            moveCursor('C',15-1);
            printf("%c",219);
            striker->y++;
        }
    }
}
}

uint16_t checkWallCollision(struct ball_t * ball, struct game_state_t *gs){
    int8_t bottomHit = 0;

    if ( ballMoveX(ball) >> 14 <= X1){ // Top wall
        ball->angle = 256-ball->angle;
        ball->x = (X1+1) << 14;
        if (gs->randomAnglePowerup){
        ball->angle = (tid.randomAngle &=0xD4)+404; // Random angle between 404 and 104
        }
    } else if (ballMoveX(ball) >>14 >= X2){  // Die condition
        bottomHit = 1;
    }
    if ( ballMoveY(ball) >> 14 <= Y1){  // Left  Wall
        ball->angle = 512 - ball->angle;
        ball->y = (Y1+1) << 14;
        if (gs->randomAnglePowerup){
        ball->angle = (tid.randomAngle &=0xD4)+20; // Random angle between 20 and 232
        }
    } else if (ballMoveY(ball) >> 14 >= Y2){ // Right wall
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

    // Striker is divided into 5 sections

//    if(ballMoveX(ball) >> 14 == striker->x || ball->x >> 14 == striker->x){
//        if(((ball->y >> 14) >= striker->y-1 && (ball->y >> 14) <= striker->y+1) || (ballMoveY(ball) >> 14 >= striker->y-1 && ballMoveY(ball) >> 14 <= striker->y+1) ){ //Middle
//
//            ball->angle = 256-ball->angle;
//            hit = 1;
//
//        } else if(((ball->y >> 14) >= striker->y-4 && (ball->y >> 14) <= striker->y-2) || (ballMoveY(ball) >> 14 >= striker->y-4 && ballMoveY(ball) >> 14 <= striker->y-2) ){ //Left medium
//
//            ball->angle = ball->angle < 128 ? 256-(ball->angle*2)/3 : 256-(ball->angle*3)/2;
//            hit = 1;
//
//        } else if(((ball->y >> 14) >= striker->y+2 && (ball->y >> 14) <= striker->y+4) || (ballMoveY(ball) >> 14 >= striker->y+2 && ballMoveY(ball) >> 14 <= striker->y+4) ){ //Right medium
//
//            ball->angle = ball->angle < 128 ? 256-(ball->angle*3)/2 : 256-(ball->angle*2)/3;
//            hit = 1;
//
//        } else if(((ball->y >> 14) >= striker->y-7 && (ball->y >> 14) <= striker->y-5) || (ballMoveY(ball) >> 14 >= striker->y-7 && ballMoveY(ball) >> 14 <= striker->y-5) ){ //Left end
//
//            if (ball->angle < 128){ // Ball hits from left
//                ball->angle = 256-ball->angle/3;
//            } else if( ball->angle > 384){ // Ball hits from right
//                ball->angle = 256-ball->angle*3;
//                if (ball->angle < 128){
//                    ball->angle = -ball->angle;
//                }
//            }
//            hit = 1;
//
//        } else if(((ball->y >> 14) >= striker->y+5 && (ball->y >> 14) <= striker->y+7) || (ballMoveY(ball) >> 14 >= striker->y+5 && ballMoveY(ball) >> 14 <= striker->y+7) ){ //Right end
//
//            if (ball->angle < 128){ // Ball hits from left
//                ball->angle = 256-ball->angle*3;
//                if (ball->angle > 384){
//                    ball->angle = -ball->angle;
//                }
//            } else if( ball->angle > 384){ // Ball hits from right
//                ball->angle = 256-ball->angle/3;
//            }
//            hit = 1;
//        }
//
//        if (hit){
//            ball->angle &= 511; // Sets angle within interval [0;511]
//            ball->x = (striker->x-1) << 14;
//            if (ball->angle > 364){
//                ball->angle = 364; // Corrects balls with wrong angle to the left
//            } else if (ball->angle < 148){
//                ball->angle = 148; // Corrects ball with wrong angle to the right
//            }
//        }
//
//    }

    if(ballMoveX(ball) >> 14 == striker->x){
        if(((ball->y >> 14) >= striker->y-1 && (ball->y >> 14) <= striker->y+1)){ //Middle

            ball->angle = 256-ball->angle;
            hit = 1;

        } else if(((ball->y >> 14) >= striker->y-4 && (ball->y >> 14) <= striker->y-2)){ //Left medium

            ball->angle = ball->angle < 128 ? 256-(ball->angle*2)/3 : 256-(ball->angle*3)/2;
            hit = 1;

        } else if(((ball->y >> 14) >= striker->y+2 && (ball->y >> 14) <= striker->y+4)){ //Right medium

            ball->angle = ball->angle < 128 ? 256-(ball->angle*3)/2 : 256-(ball->angle*2)/3;
            hit = 1;

        } else if(((ball->y >> 14) >= striker->y-7 && (ball->y >> 14) <= striker->y-5)){ //Left end

            if (ball->angle < 128){ // Ball hits from left
                ball->angle = 256-ball->angle/3;
            } else if( ball->angle > 384){ // Ball hits from right
                ball->angle = 256-ball->angle*3;
                if (ball->angle < 128){
                    ball->angle = -ball->angle;
                }
            }
            hit = 1;

        } else if(((ball->y >> 14) >= striker->y+5 && (ball->y >> 14) <= striker->y+7)){ //Right end

            if (ball->angle < 128){ // Ball hits from left
                ball->angle = 256-ball->angle*3;
                if (ball->angle > 384){
                    ball->angle = -ball->angle;
                }
            } else if( ball->angle > 384){ // Ball hits from right
                ball->angle = 256-ball->angle/3;
            }
            hit = 1;
        }

        if (hit){
            ball->angle &= 511; // Sets angle within interval [0;511]
            ball->x = (striker->x-1) << 14;
            if (ball->angle > 364){
                ball->angle = 364; // Corrects balls with wrong angle to the left
            } else if (ball->angle < 148){
                ball->angle = 148; // Corrects ball with wrong angle to the right
            }
        }

        if (gs->randomAnglePowerup){
            ball->angle = (tid.randomAngle &=0xD4)+148; // Random angle between 148 and 360
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
                       if(ball->angle == 320){ // Checks angle and determines exit angle
                           ball->angle = 64;
                       } else if(ball->angle > 320){
                            ball->angle = 512-ball->angle;
                       } else if (ball->angle < 320){
                           ball->angle = 256-ball->angle;
                       }
                   } else if( (ballMoveX(ball) >> 14 == blocks[i].x+1 && ballMoveY(ball) >> 14 ==blocks[i].y) ){ // Bottom Left Corner
                       hit = 1;
                       if(ball->angle == 192){ // Checks angle and determines exit angle
                           ball->angle = 448;
                       } else if(ball->angle > 192){
                           ball->angle = 256-ball->angle;
                       } else if (ball->angle < 192){
                           ball->angle = 512-ball->angle;
                       }
                   } else if( (ballMoveX(ball) >> 14 == blocks[i].x && ballMoveY(ball) >> 14 ==blocks[i].y+14) ){ // Top right Corner
                       hit = 1;
                       if(ball->angle == 64){ // Checks angle and determines exit angle
                           ball->angle = 320;
                       } else if(ball->angle > 64){
                           ball->angle = 512-ball->angle;
                       } else if (ball->angle < 64){
                           ball->angle = 256-ball->angle;
                       }
                   } else if((ballMoveX(ball) >> 14 == blocks[i].x+1 && ballMoveY(ball) >> 14 ==blocks[i].y+14) ){ // Bottom right Corner
                       hit = 1;
                       if(ball->angle == 448){ // Checks angle and determines exit angle
                           ball->angle = 192;
                       } else if(ball->angle > 448){
                           ball->angle = 256-ball->angle;
                       } else if (ball->angle < 448){
                           ball->angle = 512-ball->angle;
                       }
                }
			}

//            if(ball->x >> 14 == blocks[i].x || ball->x >> 14 == blocks[i].x+1  || ballMoveX(ball) >> 14 == blocks[i].x || ballMoveX(ball) >> 14 == blocks[i].x+1 ){ // Check if ball hits from top or bottom
//                if((ball->y >> 14 >= blocks[i].y+1 && ball->y >> 14 <= blocks[i].y+13) || (ballMoveY(ball) >> 14 >= blocks[i].y+1 && ballMoveY(ball) >> 14 <= blocks[i].y+13) ){ // Top and bottom sides
//                       ball->angle = 256-ball->angle;
//                       hit = 1;
//                   } else if( (ball->x >> 14 == blocks[i].x && ball->y >> 14 == blocks[i].y) || (ballMoveX(ball) >> 14 == blocks[i].x && ballMoveY(ball) >> 14 ==blocks[i].y)  ){ // Top Left Corner
//                       hit = 1;
//                       if(ball->angle == 320){ // Checks angle and determines exit angle
//                           ball->angle = 64;
//                       } else if(ball->angle > 320){
//                            ball->angle = 512-ball->angle;
//                       } else if (ball->angle < 320){
//                           ball->angle = 256-ball->angle;
//                       }
//                   } else if( (ball->x >> 14 == blocks[i].x+1 && ball->y >> 14 == blocks[i].y) || (ballMoveX(ball) >> 14 == blocks[i].x+1 && ballMoveY(ball) >> 14 ==blocks[i].y) ){ // Bottom Left Corner
//                       hit = 1;
//                       if(ball->angle == 192){ // Checks angle and determines exit angle
//                           ball->angle = 448;
//                       } else if(ball->angle > 192){
//                           ball->angle = 256-ball->angle;
//                       } else if (ball->angle < 192){
//                           ball->angle = 512-ball->angle;
//                       }
//                   } else if( (ball->x >> 14 == blocks[i].x && ball->y >> 14 == blocks[i].y+14) || (ballMoveX(ball) >> 14 == blocks[i].x && ballMoveY(ball) >> 14 ==blocks[i].y+14) ){ // Top right Corner
//                       hit = 1;
//                       if(ball->angle == 64){ // Checks angle and determines exit angle
//                           ball->angle = 320;
//                       } else if(ball->angle > 64){
//                           ball->angle = 512-ball->angle;
//                       } else if (ball->angle < 64){
//                           ball->angle = 256-ball->angle;
//                       }
//                   } else if( (ball->x >> 14 == blocks[i].x+1 && ball->y >> 14 == blocks[i].y+14) || (ballMoveX(ball) >> 14 == blocks[i].x+1 && ballMoveY(ball) >> 14 ==blocks[i].y+14) ){ // Bottom right Corner
//                       hit = 1;
//                       if(ball->angle == 448){ // Checks angle and determines exit angle
//                           ball->angle = 192;
//                       } else if(ball->angle > 448){
//                           ball->angle = 256-ball->angle;
//                       } else if (ball->angle < 448){
//                           ball->angle = 512-ball->angle;
//                       }
//                }
//			}

			if (hit == 1) { // If ball hits a block

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

void bossKey(){
 int8_t hidden=0;
 int8_t joystickKey=readJoyStick();

 if(joystickKey==2){
        if (hidden==0){
        //funktion to minimize window
        printf("\e[2t");
        hidden = 1;
        }
        joystickKey=0;
        for (int i = 0 ; i < 10000 ; i++){}

            while(joystickKey!=2){
                joystickKey=readJoyStick();
            }
        printf("\e[1t"); //funktion to maximize window
        hidden = 0;

        }

}

