#include "game.h"

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

void initFallObject(struct fallingObjectsType_t * fallObjectArray){
    memset(fallObjectArray->fallingObjectArray, 0, 10);
    fallObjectArray->numberOfObjects = 0;
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
    gs->randomAnglePowerup = 0;
    gs->I2C_Active = 0;

    I2C_Write(152,0x07,1);
    I2C_Write(152,0x01,0);


/** Include to reset highscore list   **/

//    memset(gs->highscores, 0x00, 10);
//    memset(gs->highscoreDate, 0x00, 10);
//    memset(gs->highscoreMonth, 0x00, 10);
//    memset(gs->highscoreMinutes, 0x00, 10);
//    memset(gs->highscoreHours, 0x00, 10);
//    memset(gs->highscorenames, 0x00, 70);
//    writeFlash(gs);
}

void playGame(struct game_state_t* gs){

    // Makes the structs needed for 1 player
    struct ball_t ball;
    struct player_t striker;
    struct level_t level;
    struct fallingObjectsType_t fallingObjects;

    int8_t delay = 0;
    int8_t oldlives, i, j;

    initFallObject(&fallingObjects); // Initializes powerups

    setTimer(gs->speed, gs->currentlevel); // Sets game speed
    gs->mirror = gs->startmirror; // Sets mirror to the chosen option

    if (gs->currentlevel == gs->startlevel){
        gs->lives = 2; // Sets the players lives
    }

    oldlives = gs->lives;// Sets oldlives to startlives at the start of the game
    initLED();

    if (gs->players == 2){ // 2-players

        // Makes the structs needed for the 2nd player
        struct ball_t ball2;
        struct player_t striker2;

        initBall(&ball,X2-7,Y1+50,0); // Initializes ball 1
        initBall(&ball2,X2-5,Y2-50,0); // Initializes ball 2
        initPlayer(&striker,X2-5,Y1+50); // Initializes striker1
        initPlayer(&striker2,X2-5,Y2-50); // Initializes striker2
        initLevel2Players(&ball,&ball2,&striker,&striker2,&level, gs); // Initializes level
        initDisplay(gs->buffer);

        while(1){
            if (get_game_flag()){ // updates game iterations

                if(delay++ > 3){ // Updates powerups
                    delay = 0;
                    j = fallingObjects.numberOfObjects;
                    for (i = 0; i < j; i++){
                        if (fallingObjects.fallingObjectArray[i].type != 0){
                            updateFallingObject2Players(&fallingObjects.fallingObjectArray[i],&striker,&striker2,gs); // check if collision with players
                        }

                    }

                }

                /** Checks if poweruptime has been reached */
                if (tid.seconds >= (gs->mirroruptime+15)){
                    gs->mirror = gs->startmirror;
                }
                if (tid.seconds >= gs->randomAnglePoweruptime+25){
                    gs->randomAnglePowerup = 0;
                }

                updatePlayerPosPotentiometer(&striker, gs, 0); // Updates striker
                updatePlayerPosPotentiometer(&striker2, gs, 1); // Updates striker2
                updateBallPos2Players(&ball, &striker, &striker2, &level, gs, &fallingObjects); // Updates the ball and the blocks
                updateBallPos2Players(&ball2, &striker2, &striker, &level, gs, &fallingObjects); // Updates the ball and the blocks
                LCD_Printer(gs); // Shows level, lives and points on the LCD
                bossKey();
                setLed(gs); // Sets the RGB LED to the appropriate color

                if (!gs->lives){ // Checks for gameover
                    chooseGameOver(gs);
                } else if (gs->lives == oldlives-1){ // Checks if any lives have been lost - Can be caused by a powerup or a lost ball
                    gs->mirror = gs->startmirror;
                    restartLevel2Players(&ball, &ball2, &striker, &striker2, &level, &fallingObjects);
                } else if (!(level.lives) && gs->currentlevel == 5){
                    chooseGameWon(gs);
                } else if (!(level.lives)){ // Checks if all blocks are destroyed
                    gs->currentlevel++;
                    playGame(gs);
                }
                oldlives = gs->lives; // Sets oldlives to the new amount of lives
            }
        }

    } else {// 1-player

        initBall(&ball,X2-7,Y2/2,0); // Initializes ball
        initPlayer(&striker,X2-5,Y2/2); // Initializes strikeren
        initLevel(&ball,&striker,&level, gs); // Initializes level
        initDisplay(gs->buffer);

        while(1){

            if (get_game_flag()){ // Updates gamer iterations

                // Checks powerups with a small delay in between
                if(delay++ > 3){
                    delay = 0;
                    j = fallingObjects.numberOfObjects;
                    for (i = 0; i < j; i++){
                        if (fallingObjects.fallingObjectArray[i].type!=0){
                            updateFallingObject(&fallingObjects.fallingObjectArray[i],&level, &striker, gs); // check if collision with player
                        }
                    }
                }

                /** Checks if poweruptime has been reached */
                if (tid.seconds >= (gs->mirroruptime+5) && gs->mirror != gs->startmirror){
                    gs->mirror = gs->startmirror;
                }
                if (tid.seconds >= gs->randomAnglePoweruptime+25 && gs->randomAnglePowerup){
                    gs->randomAnglePowerup = 0;
                }

                if (gs->I2C_Active){
                    updatePlayerPosI2C(&striker,gs); // Updates the striker with I2C
                } else{
                    updatePlayerPos(&striker, gs); // Updates the striker with joystick
                }


                updateBallPos(&ball, &striker, &level, gs, &fallingObjects); // Updates the ball and the blocks
                LCD_Printer(gs); // Shows level, lives and points on the LCD
                bossKey();
                setLed(gs); // Sets the RGB LED to the appropriate color

                if (gs->lives < 1){ // Checks for gameover
                    turnOffLED();
                    chooseGameOver(gs);
                } else if (gs->lives < oldlives){ // Checks if any lives have been lost - Can happen through a powerup or a lost ball
                    gs->mirror = gs->startmirror;
                    restartLevel(&ball, &striker, &level, &fallingObjects);
                } else if (!(level.lives) && gs->currentlevel == 5){ // Checks for last level cleared
                    turnOffLED();
                    chooseGameWon(gs);
                } else if (!(level.lives)){ // Checks if all blocks are destroyed
                    gs->currentlevel++;
                    playGame(gs);
                }
                oldlives = gs->lives; // Sets oldlives to the new amount of lives
            }
        }
    }
}

void initLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level, struct game_state_t* gs){
    uint8_t i;

    clrscr();
    level->lives = 0;

    // Loads blocks
    for (i = 0; i < 32; i++) {
        level->blocks[i] = Level[gs->currentlevel-1][i];
        if (level->blocks[i].lives > 0) {
            level->lives += level->blocks[i].lives;
        }
    }

    // Draws level
    drawWalls();
    drawBlockMap(level->blocks);
    drawball(ball);
    drawPlayer(striker);
}

void initLevel2Players(struct ball_t *ball,struct ball_t * ball2, struct player_t *striker, struct player_t *striker2, struct level_t *level, struct game_state_t* gs){
    uint8_t i;

    clrscr();
    level->lives = 0;

    // Loads blocks
    for (i = 0; i < 32; i++) {
        level->blocks[i] = Level[gs->currentlevel-1][i];
        if (level->blocks[i].lives > 0) {
            level->lives += level->blocks[i].lives;
        }
    }

    // Draws level
    drawWalls();
    drawBlockMap(level->blocks);
    drawball(ball);
    drawball(ball2);
    drawPlayer(striker);
    drawPlayer(striker2);
}

void restartLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level,struct fallingObjectsType_t * fallObjectArray){

        clrscr();

        // Initializes the ball, powerups and striker
        initBall(ball, X2-7, Y2/2, 0);
        initFallObject(fallObjectArray);
        striker->x = X2-5;
        striker->y = Y2/2;

        // Draws the level
        drawWalls();
        drawBlockMap(level->blocks);
        drawball(ball);
        drawPlayer(striker);
}

void restartLevel2Players(struct ball_t *ball, struct ball_t * ball2, struct player_t *striker, struct player_t * striker2, struct level_t *level,struct fallingObjectsType_t * fallObjectArray){
        clrscr();

        initBall(ball,X2-7,Y2/2,0);
        initFallObject(fallObjectArray);
        striker->x =X2-5;
        striker->y = Y2/2;

        initBall(ball,X2-7,Y1+50,0); // Initializes ball 1
        initBall(ball2,X2-5,Y2-50,0); // Initializes ball 2
        striker->x = X2-5;
        striker->y = Y1+50;
        striker2->x = X2-5;
        striker2->y = Y2-50;

        drawWalls();
        drawBlockMap(level->blocks);
        drawball(ball);
        drawball(ball2);
        drawPlayer(striker);
        drawPlayer(striker2);
}

void updatePlayerPosPotentiometer(struct player_t * striker, struct game_state_t * gs, int8_t playerNo){ // Updates player position using potentiometer
    fgcolor(15);
    static uint16_t oldPlayerx, oldPLayery;
    oldPlayerx = striker->x;
    oldPLayery = striker->y;

    if (!gs->mirror){ // Without mirror mode
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
    } else{ // with mirror mode
        if(playerNo){ // Right Player
            if(readADC_pa1() > 3300){ // Left
                if(oldPLayery-1 >= 120+8){
                    gotoxy(oldPlayerx,oldPLayery+7);
                    printf(" ");
                    moveCursor('D',15+1);
                    printf("%c",219);
                    striker->y -=1;
                }
            } else if (readADC_pa1() < 2700){ //Right
                if (oldPLayery+1 <= Y2-7){
                    gotoxy(oldPlayerx,oldPLayery-7);
                    printf(" ");
                    moveCursor('C',15-1);
                    printf("%c",219);
                    striker->y +=1;
                }
            }

        } else{ // Left player
            if(readADC_pa0() > 3300){ // Left
                if(oldPLayery-1 >= Y1+8){
                    gotoxy(oldPlayerx,oldPLayery+7);
                    printf(" ");
                    moveCursor('D',15+1);
                    printf("%c",219);
                    striker->y -=1;
                }
            } else if (readADC_pa0() < 2700){ //Right
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

}

void updatePlayerPos(struct player_t *striker, struct game_state_t* gs){ // Updates player position using joystick
    fgcolor(15);
    static uint16_t oldPlayerx,oldPLayery;
    oldPlayerx = striker->x;
    oldPLayery = striker->y;


    if (gs->mirror) { // With mirror mode
            if (readJoyStickContinous() == 8){  //Left
                if(oldPLayery-1 >= Y1+8){
                    gotoxy(oldPlayerx,oldPLayery+7);
                    printf(" ");
                    moveCursor('D',15+1);
                    printf("%c",219);
                    striker->y--;
                }
            } else if (readJoyStickContinous() == 4){    // Right
                if (oldPLayery+1 <= Y2-7){
                    gotoxy(oldPlayerx,oldPLayery-7);
                    printf(" ");
                    moveCursor('C',15-1);
                    printf("%c",219);
                    striker->y++;
                }
            }
    } else { // Without mirror mode
            if (readJoyStickContinous() == 4){  //Left
                if(oldPLayery-1 >= Y1+8){
                    gotoxy(oldPlayerx,oldPLayery+7);
                    printf(" ");
                    moveCursor('D',15+1);
                    printf("%c",219);
                    striker->y--;
                }
            } else if (readJoyStickContinous() == 8){    // Right
                if (oldPLayery+1 <= Y2-7){
                    gotoxy(oldPlayerx,oldPLayery-7);
                    printf(" ");
                    moveCursor('C',15-1);
                    printf("%c",219);
                    striker->y++;
                }
            }
    }
}

void updatePlayerPosI2C(struct player_t * striker, struct game_state_t * gs){ // Updates player position using accelerometer
    fgcolor(15);
    static uint16_t oldPlayerx,oldPLayery;
    oldPlayerx = striker->x;
    oldPLayery = striker->y;

    uint8_t j = I2C_Read(152,0x01);

    int8_t value = (int8_t)(j<<2)/4;


    if (gs->mirror) { // With mirror mode
        if (value >= 2 && value <= 11){  //Left
            if (oldPLayery+1 <= Y2-7){
                gotoxy(oldPlayerx,oldPLayery-7);
                printf(" ");
                moveCursor('C',15-1);
                printf("%c",219);
                striker->y++;
            }
        } else if (value <= -2 && value >= -11){    // Right
            if(oldPLayery-1 >= Y1+8){
                gotoxy(oldPlayerx,oldPLayery+7);
                printf(" ");
                moveCursor('D',15+1);
                printf("%c",219);
                striker->y--;
            }
        } else if (value >= 11){    // Far Left
            if (oldPLayery+2 <= Y2-7){
                gotoxy(oldPlayerx,oldPLayery-7);
                printf("  ");
                moveCursor('C',15-2);
                printf("%c%c",219,219);
                striker->y +=2;
            }
        } else if (value <= -11){    // Far Right
            if(oldPLayery-2 >= Y1+8){
                gotoxy(oldPlayerx,oldPLayery+6);
                printf("  ");
                moveCursor('D',15+2);
                printf("%c%c",219,219);
                striker->y -= 2;
            }
        }
    } else { // Without mirror mode
        if (value >= 2 && value <= 11){  //Left
            if(oldPLayery-1 >= Y1+8){
                gotoxy(oldPlayerx,oldPLayery+7);
                printf(" ");
                moveCursor('D',15+1);
                printf("%c",219);
                striker->y--;
            }
        } else if (value <= -2 && value >= -11){    // Right
            if (oldPLayery+1 <= Y2-7){
                gotoxy(oldPlayerx,oldPLayery-7);
                printf(" ");
                moveCursor('C',15-1);
                printf("%c",219);
                striker->y++;
            }
        } else if (value >= 11){    // Far Left
            if(oldPLayery-2 >= Y1+8){
                gotoxy(oldPlayerx,oldPLayery+6);
                printf("  ");
                moveCursor('D',15+2);
                printf("%c%c",219,219);
                striker->y -= 2;
            }
        } else if (value <= -11){    // Far Right
            if (oldPLayery+2 <= Y2-7){
                gotoxy(oldPlayerx,oldPLayery-7);
                printf("  ");
                moveCursor('C',15-2);
                printf("%c%c",219,219);
                striker->y +=2;
            }
        }

    }
}

void bossKey(){
 int8_t hidden=0;
 int8_t joystickKey=readJoyStick();

 if(joystickKey==2){
        if (hidden==0){
        // Function to minimize window
        printf("\e[2t");
        hidden = 1;
        }
        joystickKey=0;
        for (int i = 0 ; i < 10000 ; i++){}

            while(joystickKey!=2){
                joystickKey=readJoyStick();
            }
        printf("\e[1t"); // Function to maximize window
        hidden = 0;

        }

}
