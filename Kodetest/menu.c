#include "menu.h"
#define INCRY 25
#define INCRX 2
#define X1 30
#define X2 54
#define Y1 100
#define Y2 150

void chooseMenuOptions(){
    uint8_t k = 1;
    uint8_t q = 0;
    uint8_t highscores[5] = {25, 23, 20, 1, 0};
    uint8_t n = 0;

    drawMenuWindow();
    gotoxy(X1 + INCRX + (k<<1), Y1 + INCRY);
    printf("<<");
    while(1) {
        q = readJoyStick();
        if (q == 1) {
            if (k > 1) {
                gotoxy(X1 + INCRX + (k<<1), Y1 + INCRY);
                printf("  ");                   //Fjerner pilen
                k--;
                gotoxy(X1 + INCRX + (k<<1), Y1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (q == 2) {
            if (k < 4) {
                gotoxy(X1 + INCRX + (k<<1), Y1 + INCRY);
                printf("  ");                   //Fjerner pilen
                k++;
                gotoxy(X1 + INCRX + (k<<1), Y1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (q == 8) {
            if (k == 1) {
                drawPlayWindow();
//                chooseLevel();
            } else if (k == 2) {
                drawOptionWindow();
                chooseOptions(X1, Y1);
            } else if (k == 3) {
                drawHighscoreWindow(highscores);
                chooseHighscore();
            } else {
                drawHelpWindow();
                chooseHelp();
            }
        }
        if (n != q){
            n = q;
        }
    }
}

void chooseLevel(){
    uint8_t k = 1;
    int8_t n = 0;
    uint8_t q = 0;
    //INSERT LEVEL MAPS!

    gotoxy(X1 + 2 + (k<<1), Y1 + INCRY);
    printf("<<");
    while(1) {
        q = readJoyStick();
        if (q == 1) { //Up
            if (k > 1) {
                gotoxy(X1 + INCRX + (k<<1), Y1 + INCRY);
                printf("  ");                   //Fjerner pilen
                k--;
                gotoxy(X1 + INCRX + (k<<1), Y1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (q == 2) { //Down
            if (k < 5) {
                gotoxy(X1 + INCRX + (k<<1), Y1 + INCRY);
                printf("  ");                   //Fjerner pilen
                k++;
                gotoxy(X1 + INCRX + (k<<1), Y1 + INCRY);
                printf("<<");                   //Laver pilen
            }
//        } else if (q == 8) { //Right - Select
//            if (k == 1) {
//                initLevel(Level1);
//            } else if (k == 2) {
//                initLevel(Level2);
//            } else if (k == 3) {
//                initLevel(Level3);
//            } else if (k == 4){
//                initLevel(Level4);
//            } else {
//                initLevel(Level5);
//            }
        } else if (q == 4) { //Left - Go back
            chooseMenuOptions();
        }
        if (n != q){
            n = q;
        }
    }
}

void chooseOptions() {
    uint8_t k = 1;
    int8_t n = 0;
    uint8_t q = 0;

    while(1) {
        q = readJoyStick();
        if (q == 1) { //Up
            gotoxy(X1 + INCRX + (k<<1), Y1 + 30);
            printf("  ");                   // Fjerner pilen
            k = 1;
            gotoxy(X1 + INCRX + (k<<1), Y1 + 30);
            printf("<<");                   // Laver pilen
        } else if (q == 2) { //Down
            gotoxy(X1 + INCRX + (k<<1), Y1 + 30);
            printf("  ");                   // Fjerner pilen
            k = 2;
            gotoxy(X1 + INCRX + (k<<1), Y1 + 30);
            printf("<<");                   // Laver pilen
        } else if (q == 8) { //Right - Select
            if (k == 1) {
                gotoxy(30+INCRX+2,100+28);
                printf("1");
                changeSpeed();
            } else {
 //               toggleMirrorMode();
            }
        } else if (q == 4) {//Left - Go back
            chooseMenuOptions();
        }
        if (n != q){
            n = q;
        }
    }
}

void chooseHighscore() {
    int8_t n = 0;
    uint8_t q = 0;

    while(1) {
        q = readJoyStick();
        if (q == 4) {//Left - Go back
            chooseMenuOptions();
        }
        if (n != q){
            n = q;
        }
    }
}

void chooseHelp() {
    int8_t n = 0;
    uint8_t q = 0;
    while(1) {
        q = readJoyStick();
        if (q == 4) {//Left - Go back
            chooseMenuOptions();
        }
        if (n != q){
            n = q;
        }
    }
}

uint8_t changeSpeed(){
    static uint8_t k = 1;
    uint8_t q = 0;
    uint8_t n = 0;
    while(1) {
       q = readJoyStick();
        if (q == 1) {
            if (k < 5){
                k++;
                gotoxy(30+INCRX+2,100+28);
                printf("%d", k);
            }
        } else if (q == 2) {
            if (k > 1) {
                k--;
                gotoxy(30+INCRX+2,100+28);
                printf("%d", k);

            }
        } else if (q == 4) {
            return k; //Ændrer senere
        }
        if (n != q){
            n = q;
        }
    }
}


void drawMenuWindow() {
    char str[] = " Menu ";

    window(X1, Y1, X2, Y2, str, 1);
    gotoxy(X1+INCRX+2,Y1+10);
    printf("Play");
    gotoxy(X1+INCRX+4,Y1+10);
    printf("Options");
    gotoxy(X1+INCRX+6,Y1+10);
    printf("Highscore");
    gotoxy(X1+INCRX+8,Y1+10);
    printf("Help");
}


void drawPlayWindow() {
    char str[] = " Level ";

    window(X1, Y1, X2, Y2, str, 1);
    gotoxy(X1+INCRX+2,Y1+10);
    printf("Level 1");
    gotoxy(X1+INCRX+4,Y1+10);
    printf("Level 2");
    gotoxy(X1+INCRX+6,Y1+10);
    printf("Level 3");
    gotoxy(X1+INCRX+8,Y1+10);
    printf("Level 4");
    gotoxy(X1+INCRX+10,Y1+10);
    printf("Level 5");
}



void drawOptionWindow() {
    char str[] = " Options ";

    window(X1, Y1, X2, Y2, str, 1);
    gotoxy(X1+INCRX+2,Y1+20);
    printf("Speed: ");
    gotoxy(X1+INCRX+4,Y1+20);
    printf("Mirrormode: ");
}


void drawHighscoreWindow(uint8_t *highscores) {
    char str[] = " Highscores ";

    window(X1, Y1, X2, Y2, str, 1);
    //Highscorelist
    gotoxy(X1+INCRX+2,Y1+10);
    underline(1);
    printf("Highscores");
    underline(0);
    gotoxy(X1+INCRX+4,Y1+10);
    printf("1. %3d", highscores[0]);
    gotoxy(X1+INCRX+6,Y1+10);
    printf("2. %3d", highscores[1]);
    gotoxy(X1+INCRX+8,Y1+10);
    printf("3. %3d", highscores[2]);
    gotoxy(X1+INCRX+10,Y1+10);
    printf("4. %3d", highscores[3]);
    gotoxy(X1+INCRX+12,Y1+10);
    printf("5. %3d", highscores[4]);
}

void drawHelpWindow() {
    char str[] = " Help ";

    window(X1, Y1, X2, Y2, str, 1);
    //Game controls
    gotoxy(X1+INCRX+2, Y1+10);
    underline(1);
    printf("Game Controls:");
    underline(0);
    gotoxy(X1+INCRX+3, Y1+10);
    printf("- Use the joystick on the board.");
    gotoxy(X1+INCRX+4, Y1+10);
    printf("- Push left to go to the left.");
    gotoxy(X1+INCRX+5, Y1+10);
    printf("- Push right to go to the right.");
    gotoxy(X1+INCRX+6, Y1+10);
    printf("- Push up to start the game.");
    //Menu controls
    gotoxy(X1+INCRX+8, Y1+10);
    underline(1);
    printf("Menu Controls:");
    underline(0);
    gotoxy(X1+INCRX+9, Y1+10);
    printf("- Use the joystick on the board.");
    gotoxy(X1+INCRX+10, Y1+10);
    printf("- Push left to go to back.");
    gotoxy(X1+INCRX+11, Y1+10);
    printf("- Push right to go to select.");
    gotoxy(X1+INCRX+12, Y1+10);
    printf("- Push up to go up.");
    gotoxy(X1+INCRX+13, Y1+10);
    printf("- Push down to go down.");
}
