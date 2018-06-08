#include "menu.h"

void chooseMenuOptions(){
    uint8_t k = 1;
    uint8_t x1 = 15;
    uint8_t y1 = 15;
    uint8_t highscores[5] = {25, 23, 20, 1, 0};
    uint8_t n = 0;

    drawMenuWindow(x1, y1, 1);
    gotoxy(x1 + 2, y1 + 15);
    printf("<<");
    while(1) {
        if (readJoyStick() == 1 && n != readJoyStick()) {
            if (k > 1) {
                gotoxy(x1 + 1 + k, y1 + 15);
                printf("  ");
                k--;
                gotoxy(x1 + 1 + k, y1 + 15);
                printf("<<");
            }
        } else if (readJoyStick() == 2 && n != readJoyStick()) {
            if (k < 4) {
                gotoxy(x1 + 1 + k, y1 + 15);
                printf("  ");
                k++;
                gotoxy(x1 + 1 + k, y1 + 15);
                printf("<<");
            }
        } else if (readJoyStick() == 8 && n != readJoyStick()) {
            if (k == 1) {
                drawPlayWindow(x1, y1, 1);
//                chooseLevel();
            } else if (k == 2) {
                drawOptionWindow(x1, y1, 1);
                chooseOptions;
            } else if (k == 3) {
                drawHighscoreWindow(x1, y1, 1, highscores);
                chooseHighscore();
            } else {
 //               drawHelpWindow(x1, y1, 1);
                chooseHelp();
            }
        }
        if (n != readJoyStick()){
            n = readJoyStick();
        }
    }
}
/*
void chooseLevel(){
    uint8_t k = 1;
    uint8_t n = 0;
    //INSERT LEVEL MAPS!
    while(1) {
        if (readJoyStick() == 1) { //Up
            if (k > 1) {
                k--;
            }
        } else if (readJoyStick() == 2) { //Down
            if (k < 5) {
                k++;
            }
        } else if (readJoyStick() == 8) { //Right - Select
            if (k == 1) {
                initLevel(Level1);
            } else if (k == 2) {
                initLevel(Level2);
            } else if (k == 3) {
                initLevel(Level3);
            } else if (k == 4){
                initLevel(Level4);
            } else {
                initLevel(Level5);
            }
        } else if (readJoyStick() == 4) { //Left - Go back
            chooseMenuOptions();
        }
        if (n != readJoyStick()){
            n = readJoyStick();
        }
    }
}
*/
void chooseOptions() {
    uint8_t k = 1;
    uint8_t n = 0;
    while(1) {
        if (readJoyStick() == 1) { //Up
            k = 1;
        } else if (readJoyStick() == 2) { //Down
            k = 2;
        } else if (readJoyStick() == 8) { //Right - Select
            if (k == 1) {
 //               changeSpeed();
            } else {
 //               toggleMirrorMode();
            }
        } else if (readJoyStick() == 4) {//Left - Go back
            chooseMenuOptions();
        }
        if (n != readJoyStick()){
            n = readJoyStick();
        }
    }
}

void chooseHighscore() {
    uint8_t n = 0;
    while(1) {
        if (readJoyStick() == 4 && n != readJoyStick()) {//Left - Go back
            chooseMenuOptions();
        }
        if (n != readJoyStick()){
            n = readJoyStick();
        }
    }
}

void chooseHelp() {
    uint8_t n = 0;
    while(1) {
        if (n != readJoyStick()){
            n = readJoyStick();
        }
        if (readJoyStick() == 4) {//Left - Go back
            chooseMenuOptions();
        }
    }
}


int8_t drawMenuWindow(int8_t x1, int8_t y1, int8_t style) {
    int8_t x2 = x1+10;
    int8_t y2 = y1+30;
    char str[] = " Menu ";

    window(x1, y1, x2, y2, str, style);
    gotoxy(x1+2,y1+2);
    printf("Play");
    gotoxy(x1+3,y1+2);
    printf("Options");
    gotoxy(x1+4,y1+2);
    printf("Highscore");
    gotoxy(x1+5,y1+2);
    printf("Help");
    return 1;
}


void drawPlayWindow(int8_t x1, int8_t y1, int8_t style) {
    int8_t x2 = x1+10;
    int8_t y2 = y1+30;
    char str[] = " Level ";

    window(x1, y1, x2, y2, str, style);
    gotoxy(x1+2,y1+2);
    printf("Level 1");
    gotoxy(x1+3,y1+2);
    printf("Level 2");
    gotoxy(x1+4,y1+2);
    printf("Level 3");
    gotoxy(x1+5,y1+2);
    printf("Level 4");
    gotoxy(x1+6,y1+2);
    printf("Level 5");
}



void drawOptionWindow(int8_t x1, int8_t y1, int8_t style) {
    int8_t x2 = x1+10;
    int8_t y2 = y1+30;
    char str[] = " Options ";

    window(x1, y1, x2, y2, str, style);
    gotoxy(x1+1,y1+2);
    printf("Mirror mode");
    gotoxy(x1,y1);
    printf("Speed mode");
}


void drawHighscoreWindow(int8_t x1, int8_t y1, int8_t style, uint8_t *highscores) {
    int8_t x2 = x1+10;
    int8_t y2 = y1+30;
    char str[] = " Highscores ";

    window(x1, y1, x2, y2, str, style);
    gotoxy(x1+2,y1+2);
    printf("Highscores");
    gotoxy(x1+3,y1+2);
    printf("1. %3d", highscores[0]);
    gotoxy(x1+4,y1+2);
    printf("2. %3d", highscores[1]);
    gotoxy(x1+5,y1+2);
    printf("3. %3d", highscores[2]);
    gotoxy(x1+6,y1+2);
    printf("4. %3d", highscores[3]);
    gotoxy(x1+7,y1+2);
    printf("5. %3d", highscores[4]);
}
