
#include "gamePhysics.h"

void initBall (struct ball_t* ball, int32_t x, int32_t y, int32_t speed)
{
    ball->x = x << 14;
    ball-> y = y << 14;
    ball->speed = FIX14_MULT(speed << 14, 7000);
    ball->angle = (tid.centiseconds &=0x7F)+192; // Angle between 192 and 319
//    ball->vec.x = FIX14_MULT(dx << 14, 5000);
//    ball->vec.y = FIX14_MULT(dy << 14, 5000);
}

void initPlayer(struct player_t * striker, uint16_t x, uint16_t y)
{
    striker->x = x;
    striker->y = y;
}

void initGameState(struct game_state_t* gs)
{
    gs->speed = 1;
    gs->mirror = 0;
    memset(gs->highscores, 0x00, 5);
    gs->points = 0;
    gs->lives = 0;
    gs->startlevel = 0;
    gs->currentlevel = 0;
}

/*void activatePowerUps(struct game_state_t* gs)
{
    int8_t type=0;

    if (type==2)
    {
        printf("wuhuuuuuu");
        gs->lives++;
    }
    else if (type==1)
    {
        printf("BOOOOOOOOOOOOM");
        gs->lives--;
    }
}

*/


void CheckHitWithPlayer(struct object *fallObject, struct player_t * striker, struct game_state_t* gs)
{
    static uint8_t mirroruptime, rangleuptime;

    if(fallObject->y <= striker->y+7 && fallObject->x+1 == striker->x && fallObject->y >= striker->y-7)
    {
            //activatePowerUps();
            if(fallObject->type==1)
            {
                printf("Dead");
                gs->lives--;
                fallObject->type=0;
            }else if (fallObject->type==2)
            {
                printf("wuhuu");
                gs->lives++;
                fallObject->type=0;
            }else if (fallObject->type==3)
            {
                mirroruptime = tid.seconds;
                printf("Mirror-Mode!");
                gs->mirror=!gs->mirror;
                fallObject->type = 7;
            }else if (fallObject->type==4)
            {
                rangleuptime = tid.seconds;
                printf("Random angle");
            }
//            }else if (fallObject->type==5)
//            {
//                printf("Long-Strikker");
//
//            }else if (fallObject->type==6)
//            {
//                printf("Slippi-Mode");
//
//            }else if (fallObject->type==7)
//            {
//                printf("One More Ball");
//
//            }
fallObject->type=0;
    }
    if (fallObject->type == 7 && tid.seconds >= mirroruptime+5){
        gs->mirror=!gs->mirror;
        fallObject->type = 0;
    } else if (fallObject->type == 4 && tid.seconds >= rangleuptime+5){
        fallObject->type = 0;
    }


}









int printfallObject(struct object *fallObject)
{
    int returnValue =0;
    gotoxy(fallObject->x, fallObject->y);
    printf(" ");
    fallObject->x++;
    if (fallObject->x==X2)
    {
        fallObject->type=0; //None
        //check if hit    -  mangler at tjekke for hit
        //tjek om den rammer playeren!!!!!!!!!!!!!!!!!!!!!!!!!!!

//        checkPlayerPower(struct object *fallObject, struct player_t * striker);

        returnValue = 1;
    }
//    else if (!(fallObject->type == 1 || fallObject->type == 2 || fallObject->type == 3 || fallObject->type == 4 || fallObject->type == 7 || fallObject->type == 0))
//    {
        gotoxy(fallObject->x, fallObject->y);
        if (fallObject->type==1)
        {
            fgcolor(1);
            printf("%c", 219);
        }
        else if(fallObject->type==2)
        {
            fgcolor(2);
            printf("%c", 219);
        }else if(fallObject->type==3)
        {
            fgcolor(3);
            printf("%c", 219);


    }

    return returnValue;
}






























void playGame(struct game_state_t* gs)
{
    struct ball_t ball;
    struct player_t striker;
    struct level_t bane;
    struct object fallObject;


    struct fallingObjectsType fallingObjects;
    fallingObjects.numberOfObjects=0;



    //fallObject.type=0; // None
    int delay =0;
    int8_t oldlives;

    int i,j;

    setTimer(gs->speed, gs->currentlevel);
    gs->lives = 1;//Sætter spillerens liv
    initBall(&ball,X2-7,Y2/2,0);//Initialisere bolden
    initPlayer(&striker,X2-5,Y2/2);//Initialisere strikeren
    initLevel(&ball,&striker,&bane, gs);//Initialisere blokkene
    initDisplay(gs->buffer);

    oldlives = gs->lives;
    while(1)
    {

        if (get_game_flag())
        {
            delay++;
            if(delay > 3)
            {
                delay =0;
                j=fallingObjects.numberOfObjects;
               for (i=0; i<j;i++){
                if (fallingObjects.fallingObjectArray[i].type!=0)
                {
                fallObject=fallingObjects.fallingObjectArray[i];


                printfallObject(&fallObject);

                      // check if collision with player
                      CheckHitWithPlayer(&fallObject,&striker,gs);


                      fallingObjects.fallingObjectArray[i]=fallObject;

                }

                }

            }



                updatePlayerPos(&striker,gs);//Updatere strikeren
                updateBallPos(&ball,&striker,&bane, gs, &fallingObjects);//Updatere bolden og blokkene
                LCD_Printer(gs);//Viser level, liv og point på LCD
                bossKey();

                gotoxy(30,5);
                printf("%4ld",ball.angle);
                if (!gs->lives) //Tjekker om man er død
                {
                    chooseGameOver(gs);
                } else if (gs->lives == oldlives-1){//Tjekker om man har mistet liv
                    restartLevel(&ball,&striker,&bane);
                }
                oldlives = gs->lives;
        }
    }
}

void initLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level, struct game_state_t* gs)
{
    clrscr();
    uint8_t i;

    level->lives = 0;

    for (i = 0; i < 32; i++)
    {
        level->blocks[i] = Level[gs->currentlevel-1][i];
        if (level->blocks[i].lives > 0)
        {
            level->lives += level->blocks[i].lives;
        }
    }
    drawWalls();
    drawBlockMap(level->blocks);
    drawball(ball);
    drawPlayer(striker);
}


void restartLevel(struct ball_t *ball, struct player_t *striker, struct level_t *level)
{
    clrscr();

    initBall(ball,X2-7,Y2/2,0);
    striker->x =X2-5;
    striker->y = Y2/2;


    drawWalls();
    drawBlockMap(level->blocks);
    drawball(ball);
    drawPlayer(striker);
}




void updateBallPos(struct ball_t * ball,struct player_t *striker, struct level_t *level, struct game_state_t * gs,struct fallingObjectsType *fallObject_ptr)
{
    uint16_t playerhit = checkPlayerCollision(ball,striker);
    uint16_t wallhit = checkWallCollision(ball);
    checkBlockCollision(ball, level, gs, fallObject_ptr);

    if (ball->angle < 0)
    {
        ball->angle &= 511; // Makes angle positive
    }
    static int32_t oldx, oldy;
    oldx= ball->x;
    oldy = ball->y;


    if ( ball->speed == 0)
    {
        ball->x = (striker->x-2) << 14;
        ball->y = (striker->y) << 14;
        if ( readJoyStickContinous() == 16)
        {
            ball->speed = FIX14_MULT(1 << 14, 8000);
//                ball->vec.x = -FIX14_MULT(1 << 14, 10000);
//                ball->vec.y = FIX14_MULT(1 << 14, 10000);
        }

    }



    ball->x += FIX14_MULT(ball->speed,cosinus(ball->angle));
    ball->y += FIX14_MULT(ball->speed,sinus(ball->angle));


    // Makes sure ball doesn't exceed bounds with larger vectors
    if (wallhit == 1)
    {
        if ( (ball->x >> 14) >= X2)
        {
            ball->x = (X2-1) << 14;
        }
        if ( (ball->x >> 14) <= X1)
        {
            ball->x = (X1+1) << 14;
        }
        if ( (ball->y >> 14) >= Y2)
        {
            ball->y = (Y2-1) << 14;
        }
        if ( (ball->y >> 14) <= Y1)
        {
            ball->y = (Y1+1) << 14;
        }
    }
    else if (wallhit ==2)    // Ball dead
    {
        gs->lives--;
    }

    if (playerhit)  // If ball hits player
    {
        ball->x = (striker->x-1) << 14;
    }
    if ( oldx != ball->x || oldy != ball->y)
    {
        gotoxy(oldx >> 14,oldy >> 14);
        printf(" ");
        drawball(ball);
    }
}

void updatePlayerPos(struct player_t *striker, struct game_state_t* gs)
{
    fgcolor(15);
    static uint16_t oldPlayerx,oldPLayery;
    oldPlayerx = striker->x;
    oldPLayery = striker->y;


if (gs->mirror) {
        if (readJoyStickContinous() == 8)  //Left
    {
//        if(oldPLayery-3 >= Y1+8){
//            gotoxy(oldPlayerx,oldPLayery+7-2);
//            printf("   ");
//            moveCursor('D',15+3);
//            printf("%c%c%c",219,219,219);
//            striker->y -= 3;
//        } else
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
//        if (oldPLayery+3 <= Y2-7){
//            gotoxy(oldPlayerx,oldPLayery-7);
//            printf("   ");
//            moveCursor('C',15-3);
//            printf("%c%c%c",219,219,219);
//            striker->y += 3;
//        } else
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
//        if(oldPLayery-3 >= Y1+8){
//            gotoxy(oldPlayerx,oldPLayery+7-2);
//            printf("   ");
//            moveCursor('D',15+3);
//            printf("%c%c%c",219,219,219);
//            striker->y -= 3;
//        } else
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
//        if (oldPLayery+3 <= Y2-7){
//            gotoxy(oldPlayerx,oldPLayery-7);
//            printf("   ");
//            moveCursor('C',15-3);
//            printf("%c%c%c",219,219,219);
//            striker->y += 3;
//        } else
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


//    if( oldPlayerx != striker->x || oldPLayery != striker->y){
//        gotoxy(oldPlayerx,oldPLayery-7);
//        printf("               ");
//        drawPlayer(striker);
//    }
}

uint16_t checkWallCollision(struct ball_t * ball)
{
    int8_t i = 0;

    if ( (ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 <= X1)  // Top wall
    {
        ball->angle = 256-ball->angle;
        i = 1;
    }
    else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >>14 >= X2)     // Die condition
    {
        i = 2;
    }
    if ( (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= Y1 || (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= Y2 )   // Left or right wall
    {
        ball->angle = 512 - ball->angle;
        i= 1;
    }

    return i;
}

uint16_t checkPlayerCollision(struct ball_t * ball, struct player_t * striker)
{
    uint16_t hit = 0;

    // Player is divided into 5 sections
    if((ball->x >> 14) == striker->x || (ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == striker->x)
    {
        if(((ball->y >> 14) >= striker->y-1 && (ball->y >> 14) <= striker->y+1)  || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y-1 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y-1))
        {
//Middle
            ball->angle = 256-ball->angle;
            hit = 1;

        }
        else if(((ball->y >> 14) >= striker->y-4 && (ball->y >> 14) <= striker->y-2) || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y-4 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y-2))
        {
//Left medium


            ball->angle = ball->angle < 128 ? 256-(ball->angle*2)/3 : 256-(ball->angle*3)/2;


            hit = 1;
        }
        else if(((ball->y >> 14) >= striker->y+2 && (ball->y >> 14) <= striker->y+4) || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y+2 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y+4))
        {
//Right medium



            ball->angle = ball->angle < 128 ? 256-(ball->angle*3)/2 : 256-(ball->angle*2)/3;

            hit = 1;
        }
        else if(((ball->y >> 14) >= striker->y-7 && (ball->y >> 14) <= striker->y-5) || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y-7 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y-5))
        {
//Left end

            if (ball->angle < 128)  // Ball hits from left
            {
                ball->angle = 256-ball->angle/3;
            }
            else if( ball->angle > 384)    // Ball hits from right
            {
                ball->angle = 256-ball->angle*3;
                if (ball->angle < 128)
                {
                    ball->angle = -ball->angle;
                }
            }

            //ball->angle = ball->angle < 128 ? 256-ball->angle/3 : 256-ball->angle*3;

            hit = 1;
        }
        else if(((ball->y >> 14) >= striker->y+5 && (ball->y >> 14) <= striker->y+7) || ((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >= striker->y+5 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <= striker->y+7))
        {
//Right end

            if (ball->angle < 128)  // Ball hits from left
            {
                ball->angle = 256-ball->angle*3;
                if (ball->angle > 384)
                {
                    ball->angle = -ball->angle;
                }
            }
            else if( ball->angle > 384)    // Ball hits from right
            {
                ball->angle = 256-ball->angle/3;
            }
            //ball->angle = ball->angle < 128 ? 256-ball->angle*3 : 256-ball->angle/3;

            hit = 1;
        }

        if (hit)
        {
            ball->angle &= 511; // Sets angle within interval [0;511]
            if (ball->angle > 364)
            {
                ball->angle = 364; // Corrects balls with wrong angle to the left
            }
            else if (ball->angle < 148)
            {
                ball->angle = 148; // Corrects ball with wrong angle to the right
            }
        }

    }
    return hit;

}

uint16_t checkBlockCollision(struct ball_t* ball, struct level_t* level, struct game_state_t * gs,struct fallingObjectsType *fallObject_ptr)
{
    uint8_t i;
    uint16_t hit;
    struct block_t * blocks = level->blocks;

    for (i = 0; i < 32; i++)
    {
        if (blocks[i].lives > 0)
        {
            hit = 0;

            // Check if ball hits from top or bottom
            if((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x || (ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x+1 )
            {
                if((ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 >=blocks[i].y+1 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 <=blocks[i].y+13)
                {
                    ball->angle = 256-ball->angle;
                    hit = 1;
                }
            }
            else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 == blocks[i].y)    // Top Left Corner
            {
                if(ball->angle == 320)
                {
                    ball->angle = 64;
                }
                else if(ball->angle > 320)
                {
                    ball->angle = 512-ball->angle;
                }
                else if (ball->angle < 320)
                {
                    ball->angle = 256-ball->angle;
                }
            }
            else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x+1 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 == blocks[i].y)    // Bottom Left Corner
            {
                if(ball->angle == 448)
                {
                    ball->angle = 192;
                }
                else if(ball->angle > 448)
                {
                    ball->angle = 256-ball->angle;
                }
                else if (ball->angle < 448)
                {
                    ball->angle = 512-ball->angle;
                }
            }
            else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 == blocks[i].y+14)    // Top Right COrner
            {
                if(ball->angle == 64)
                {
                    ball->angle = 320;
                }
                else if(ball->angle > 64)
                {
                    ball->angle = 512-ball->angle;
                }
                else if (ball->angle < 64)
                {
                    ball->angle = 256-ball->angle;
                }
            }
            else if ((ball->x+FIX14_MULT(ball->speed,cosinus(ball->angle))) >> 14 == blocks[i].x+1 && (ball->y+FIX14_MULT(ball->speed,sinus(ball->angle))) >> 14 == blocks[i].y+14)    // Bottom Right Corner
            {
                if(ball->angle == 192)
                {
                    ball->angle = 448;
                }
                else if(ball->angle > 192)
                {
                    ball->angle = 256-ball->angle;
                }
                else if (ball->angle < 192)
                {
                    ball->angle = 512-ball->angle;
                }
            }

            if (hit == 1)
            {

                blocks[i].lives--;
                drawBlock(blocks[i]);
                level->lives--;
                gs->points++;
                if (blocks[i].lives==0||blocks[i].fallingObject>0)
                {


                    fallObject_ptr->fallingObjectArray [fallObject_ptr->numberOfObjects].type = blocks[i].fallingObject;
                    fallObject_ptr->fallingObjectArray [fallObject_ptr->numberOfObjects].x=blocks[i].x;
                    fallObject_ptr->fallingObjectArray [fallObject_ptr->numberOfObjects].y=blocks[i].y;

                    fallObject_ptr->numberOfObjects++;


                }
            }

        }
    }
    return hit;
}

void bossKey()
{
    int8_t hidden=0;
    int8_t joystikKey=readJoyStick();

    if(joystikKey==2)
    {
        if (hidden==0)
        {
            //funktion to minimize window
            printf("\e[2t");
            hidden = 1;
        }
        joystikKey=0;
        for (int i = 0 ; i < 10000 ; i++) {}

        while(joystikKey!=2)
        {
            joystikKey=readJoyStick();
        }
        printf("\e[1t"); //funktion to maximize window
        hidden = 0;

    }

}
