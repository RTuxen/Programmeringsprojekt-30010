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
    memset(fallObjectArray->fallingObjectArray,0,10);
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

    // Include to reset highscorelist
//    memset(gs->highscores, 0x00, 10);
//    memset(gs->highscoreDate, 0x00, 10);
//    memset(gs->highscoreMonth, 0x00, 10);
//    memset(gs->highscoreMinutes, 0x00, 10);
//    memset(gs->highscoreHours, 0x00, 10);
//    memset(gs->highscorenames, 0x00, 70);
}

void playGame(struct game_state_t* gs){

    struct ball_t ball;
    struct player_t striker;
    struct level_t level;
    struct fallingObject_t fallObject;

    int8_t delay = 0;
    int8_t oldlives, i, j;

    struct fallingObjectsType_t fallingObjects;
    initFallObject(&fallingObjects); // Initializes powerups


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

                updatePlayerPosPotentiometer(&striker,gs,0);// Updates striker
                updatePlayerPosPotentiometer(&striker2,gs,1);// Updates striker2
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

void updatePlayerPosPotentiometer(struct player_t * striker, struct game_state_t * gs, int8_t playerNo){
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
