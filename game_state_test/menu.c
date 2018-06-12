#include "menu.h"
#define INCRY 25
#define INCRX 2
#define MENUX1 30
#define MENUX2 54
#define MENUY1 100
#define MENUY2 150

void chooseMenuOptions(struct game_state_t* gs){//Tilføj uint8_t score, så den kan modtage en score, hvis den går videre fra chooseGameOver()
    uint8_t k = 1;
    uint8_t q = 0;

    drawMenuWindow();       //Tegner Menu vinduet
    gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + INCRY);
    printf("<<");
    while(1) {
        q = readJoyStick();
        if (q == 1) {       //Hvis joystick trykkes up, så decremeres k ned til en minimums-værdi og pilen rykker op til forrige linje
            if (k > 1) {
                gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + INCRY);
                printf("  ");                   //Fjerner pilen
                k--;
                gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (q == 2) {//Hvis joystick trykkes ned, så incremeres k op til en maks-værdi og pilen rykker ned til næste linje
            if (k < 4) {
                gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + INCRY);
                printf("  ");                   //Fjerner pilen
                k++;
                gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (q == 8) {//Hvis joystick trykkes til højre, så bruges k-værdien og den tilhørende linje vælges
            if (k == 1) {       //Play vælges
                drawPlayWindow();
                chooseLevel(gs);
            } else if (k == 2) {//Options vælges
                drawOptionWindow(gs->speed);
                chooseOptions(gs);
            } else if (k == 3) {//Highscorelisten vælges
                drawHighscoreWindow(gs->highscores);
                chooseHighscore(gs);
            } else {            //Help vælges
                drawHelpWindow();
                chooseHelp(gs);
            }
        }
    }
}

void chooseLevel(struct game_state_t* gs){
    uint8_t k = 1;
    uint8_t q = 0;
    //INSERT LEVEL MAPS!

    gotoxy(MENUX1 + 2 + (k<<1), MENUY1 + INCRY);
    printf("<<");
    while(1) {
        q = readJoyStick();
        if (q == 1) { //Up
            if (k > 1) {
                gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + INCRY);
                printf("  ");                   //Fjerner pilen
                k--;
                gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (q == 2) { //Down
            if (k < 5) {
                gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + INCRY);
                printf("  ");                   //Fjerner pilen
                k++;
                gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (q == 8) { //Right - Select
            if (k == 1) {
                gs->level = k;
            } else if (k == 2) {
                gs->level = k;
            } else if (k == 3) {
                gs->level = k;
            } else if (k == 4){
                gs->level = k;
            } else {
                gs->level = k;
            }
            playGame(gs);
        } else if (q == 4) { //Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseOptions(struct game_state_t* gs) {
    uint8_t k = 1;
    uint8_t q = 0;

    while(1) {
        q = readJoyStick();
        if (q == 1) { //Up
            gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + 38);
            printf("  ");                   // Fjerner pilen
            k = 1;
            gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + 38);
            printf("<<");                   // Laver pilen
        } else if (q == 2) { //Down
            gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + 38);
            printf("  ");                   // Fjerner pilen
            k = 2;
            gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + 38);
            printf("<<");                   // Laver pilen
        } else if (q == 8) { //Right - Select
            if (k == 1) {
                changeSpeed(gs);
            } else {
 //               toggleMirrorMode(gs);
            }
        } else if (q == 4) {//Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseHighscore(struct game_state_t* gs) {
    uint8_t q = 0;

    while(1) {
        q = readJoyStick();
        if (q == 4) {//Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseHelp(struct game_state_t* gs) {
    uint8_t q = 0;

    while(1) {
        q = readJoyStick();
        if (q == 4) {//Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseGameOver(struct game_state_t* gs, uint8_t* buffer){
    uint8_t k = 1;
    uint8_t q = 0;
    int8_t i, j;

    //Sammenligner scoren med tidligere highscores
    for (i = 0; i < 5; i++){
        if (gs->points > gs->highscores[i]){
            for(j = 4; j >= i; j--){//Rykker tidligere highscores under den nye highscore én ned
                gs->highscores[j] = gs->highscores[j-1];
            }
            gs->highscores[i] = gs->points;  //Indsætter den nye highscore
            break;
        }
    }
    gs->points = 0;//Resetter scoren efter et tabt spil

    drawGameOverWindow();
    gotoxy(MENUX1 + INCRX + 2 + (k<<1), MENUY1 + 35);
    printf("<<");
    while(1) {
        q = readJoyStick();
        if (q == 1) {
            gotoxy(MENUX1 + INCRX + 2 + (k<<1), MENUY1 + 35);
            printf("  ");                   //Fjerner pilen
            k = 1;
            gotoxy(MENUX1 + INCRX + 2 + (k<<1), MENUY1 + 35);
            printf("<<");                   //Laver pilen
        } else if (q == 2) {
            gotoxy(MENUX1 + INCRX + 2 + (k<<1), MENUY1 + 35);
            printf("  ");                   //Fjerner pilen
            k = 2;
            gotoxy(MENUX1 + INCRX + 2 + (k<<1), MENUY1 + 35);
            printf("<<");                   //Laver pilen
        } else if (q == 8) {
            if (k == 1) {
                playGame(gs); //Loader det sidst tabte level
            } else {
                initDisplay(buffer);
                chooseMenuOptions(gs); //Går til menuen og uploader scoren
            }
        }
    }
}

void changeSpeed(struct game_state_t* gs){
    static uint8_t k = 1;//Bruges til at sætte hastighed
    uint8_t q = 0;

    while(1) {
        q = readJoyStick();
        if (q == 1) {
            if (k < 5){
                k++;
                gotoxy(30+INCRX+2,100+35);
                printf("%d", k);
            }
        } else if (q == 2) {
            if (k > 1) {
                k--;
                gotoxy(30+INCRX+2,100+35);
                printf("%d", k);
            }
        } else if (q == 4) {
            gs->speed = k;
            chooseOptions(gs);
        }
    }
}


void drawMenuWindow() {
    char str[] = " Menu ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str, 1);
    gotoxy(MENUX1+INCRX+2,MENUY1+10);
    printf("Play");
    gotoxy(MENUX1+INCRX+4,MENUY1+10);
    printf("Options");
    gotoxy(MENUX1+INCRX+6,MENUY1+10);
    printf("Highscore");
    gotoxy(MENUX1+INCRX+8,MENUY1+10);
    printf("Help");
}


void drawPlayWindow() {
    char str[] = " Level ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str, 1);
    gotoxy(MENUX1+INCRX+2,MENUY1+10);
    printf("Level 1");
    gotoxy(MENUX1+INCRX+4,MENUY1+10);
    printf("Level 2");
    gotoxy(MENUX1+INCRX+6,MENUY1+10);
    printf("Level 3");
    gotoxy(MENUX1+INCRX+8,MENUY1+10);
    printf("Level 4");
    gotoxy(MENUX1+INCRX+10,MENUY1+10);
    printf("Level 5");
}



void drawOptionWindow(uint8_t speed) {
    char str[] = " Options ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str, 1);
    gotoxy(MENUX1+INCRX+2,MENUY1+20);
    printf("Mirrormode: "); //Skal kunne toggles mellem On/Off
    gotoxy(MENUX1+INCRX+4,MENUY1+20);
    printf("Speed:        %d", speed);
}


void drawHighscoreWindow(uint8_t *highscores) {
    char str[] = " Highscores ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str, 1);
    //Highscorelist
    gotoxy(MENUX1+INCRX+2,MENUY1+10);
    underline(1);
    printf("Highscores");
    underline(0);
    gotoxy(MENUX1+INCRX+4,MENUY1+10);
    printf("1. %3d", highscores[0]);
    gotoxy(MENUX1+INCRX+6,MENUY1+10);
    printf("2. %3d", highscores[1]);
    gotoxy(MENUX1+INCRX+8,MENUY1+10);
    printf("3. %3d", highscores[2]);
    gotoxy(MENUX1+INCRX+10,MENUY1+10);
    printf("4. %3d", highscores[3]);
    gotoxy(MENUX1+INCRX+12,MENUY1+10);
    printf("5. %3d", highscores[4]);
}

void drawHelpWindow() {
    char str[] = " Help ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str, 1);
    //Game controls
    gotoxy(MENUX1+INCRX+2, MENUY1+10);
    underline(1);
    printf("Game Controls:");
    underline(0);
    gotoxy(MENUX1+INCRX+3, MENUY1+10);
    printf("- Use the joystick on the board.");
    gotoxy(MENUX1+INCRX+4, MENUY1+10);
    printf("- Push left to go to the left.");
    gotoxy(MENUX1+INCRX+5, MENUY1+10);
    printf("- Push right to go to the right.");
    gotoxy(MENUX1+INCRX+6, MENUY1+10);
    printf("- Push up to start the game.");
    //Menu controls
    gotoxy(MENUX1+INCRX+8, MENUY1+10);
    underline(1);
    printf("Menu Controls:");
    underline(0);
    gotoxy(MENUX1+INCRX+9, MENUY1+10);
    printf("- Use the joystick on the board.");
    gotoxy(MENUX1+INCRX+10, MENUY1+10);
    printf("- Push left to go to back.");
    gotoxy(MENUX1+INCRX+11, MENUY1+10);
    printf("- Push right to go to select.");
    gotoxy(MENUX1+INCRX+12, MENUY1+10);
    printf("- Push up to go up.");
    gotoxy(MENUX1+INCRX+13, MENUY1+10);
    printf("- Push down to go down.");
}

void drawGameOverWindow() {
    char str[] = " Game Over ";
    fgcolor(15); // White
    //Game over
    window(MENUX1, MENUY1, MENUX2, MENUY2, str, 1);
    gotoxy(MENUX1+INCRX+2,MENUY1+20);
    printf("Git gut, skrubbe!");
    gotoxy(MENUX1+INCRX+4,MENUY1+20);
    printf("Play again?");
    gotoxy(MENUX1+INCRX+6,MENUY1+20);
    printf("Go to Menu");
}
