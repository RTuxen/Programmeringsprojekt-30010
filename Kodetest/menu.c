#include "menu.h"
#define INCRY 25
#define INCRX 2
#define MENUX1 30
#define MENUX2 54
#define MENUY1 100
#define MENUY2 150

void chooseMenuOptions(uint8_t score){//Tilføj uint8_t score, så den kan modtage en score, hvis den går videre fra chooseGameOver()
    static uint8_t highscores[5] = {5, 4, 3, 2, 1}; //Skal starte med at være tom og derefter fyldes på
    uint8_t k = 1;
    uint8_t q = 0;
    uint8_t i, j;

    //Sammenligner scoren med tidligere highscores
    for (i = 4; i >= 0; i++){
        if (score > highscores[i]){
            for(j = 1; j <= i; j++){//Rykker tidligere highscores under den nye highscore én ned
                highscores[j] = highscores[j-1];
            }
            score = highscores[i];  //Indsætter den nye highscore
            break;
        }
    }

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
//                chooseLevel();
            } else if (k == 2) {//Options vælges
                drawOptionWindow();
                chooseOptions(MENUX1, MENUY1);
            } else if (k == 3) {//Highscorelisten vælges
                drawHighscoreWindow(highscores);
                chooseHighscore();
            } else {            //Help vælges
                drawHelpWindow();
                chooseHelp();
            }
        }
    }
}

void chooseLevel(){
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
            chooseMenuOptions(0);
        }
    }
}

void chooseOptions() {
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
                changeSpeed(1);
            } else {
 //               toggleMirrorMode();
            }
        } else if (q == 4) {//Left - Go back
            chooseMenuOptions(0);
        }
    }
}

void chooseHighscore() {
    uint8_t q = 0;

    while(1) {
        q = readJoyStick();
        if (q == 4) {//Left - Go back
            chooseMenuOptions(0);
        }
    }
}

void chooseHelp() {
    uint8_t q = 0;

    while(1) {
        q = readJoyStick();
        if (q == 4) {//Left - Go back
            chooseMenuOptions(0);
        }
    }
}

void chooseGameOver(uint8_t score){ //Tilføj uint8_t playerScore og Level-nummer senere
    uint8_t k = 1;
    uint8_t q = 0;

    drawMenuWindow();
    gotoxy(MENUX1 + INCRX + (k<<1), MENUY1 + 35);
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
//                initLevel(Level); //Skal loade det sidst spillede level
            } else {
                chooseMenuOptions(score);
            }
        }
    }
}

uint8_t changeSpeed(uint8_t changeValue){
    static uint8_t k = 1;//Bruges til at sætte hastighed

    if (changeValue){
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
                return k; //Ændrer senere
            }
        }
    } else {//Bruges til at hente Speed-værdien
        return k;
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



void drawOptionWindow() {
    char str[] = " Options ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str, 1);
    gotoxy(MENUX1+INCRX+2,MENUY1+20);
    printf("Mirrormode: "); //Skal kunne toggles mellem On/Off
    gotoxy(MENUX1+INCRX+4,MENUY1+20);
    printf("Speed:        %d", changeSpeed(0));
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
    //Game over
    window(MENUX1, MENUY1, MENUX2, MENUY2, str, 1);
    gotoxy(MENUX1+INCRX+2,MENUY1+20);
    printf("Git gut, skrubbe!");
    gotoxy(MENUX1+INCRX+4,MENUY1+20);
    printf("Play again?");
    gotoxy(MENUX1+INCRX+6,MENUY1+20);
    printf("Go to Menu");
}
