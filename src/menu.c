#include "menu.h"

void chooseMenuOptions(struct game_state_t* gs){//Tilføj uint8_t score, så den kan modtage en score, hvis den går videre fra chooseGameOver()
    uint8_t arrow = 1;
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;
    uint16_t t = tid.soundtime;
    uint8_t i = 0;

    clrscr();
    drawWelcomeMessage();
    setTimerDefault();
    drawMenuWindow();       //Tegner Menu vinduet
    gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
    printf("<<");
    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();

        if(tid.soundtime >= t+TEMPO[i]){
            setFreq(MELODY[i]);
            t=tid.soundtime;
            i++;
            if(i >= 81){
                i=0;
            }
        }

        if (joystickValue == 1 || keyboardValue == W) {       //Hvis joystick trykkes up, så decremeres k ned til en minimums-værdi og pilen rykker op til forrige linje
            if (arrow > 1) {
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
                printf("  ");                   //Fjerner pilen
                arrow--;
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (joystickValue == 2 || keyboardValue == S) {//Hvis joystick trykkes ned, så incremeres k op til en maks-værdi og pilen rykker ned til næste linje
            if (arrow < 4) {
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
                printf("  ");                   //Fjerner pilen
                arrow++;
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (joystickValue == 8 || keyboardValue == D) {//Hvis joystick trykkes til højre, så bruges k-værdien og den tilhørende linje vælges
            if (arrow == 1) {       //Play vælges
                drawPlayWindow();
                setFreq(0);
                chooseLevel(gs);
            } else if (arrow == 2) {//Options vælges
                clrscr();
                setFreq(0);
                drawOptionMessage();
                drawOptionWindow(gs);
                chooseOptions(gs);
            } else if (arrow == 3) {//Highscorelisten vælges
                clrscr();
                setFreq(0);
                drawHighscoreMessage();
                drawHighscoreWindow(gs->highscores);
                chooseHighscore(gs);
            } else {            //Help vælges
                clrscr();
                setFreq(0);
                drawHelpMessage();
                drawHelpWindow();
                chooseHelp(gs);
            }
        }
    }
}

void chooseLevel(struct game_state_t* gs){
    uint8_t levelNum = 1;
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;
    //INSERT LEVEL MAPS!

    gotoxy(MENUX1 + 2 + (levelNum<<1), MENUY1 + INCRY);
    printf("<<");
    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) { //Up
            if (levelNum > 1) {
                gotoxy(MENUX1 + INCRX + (levelNum<<1), MENUY1 + INCRY);
                printf("  ");                   //Fjerner pilen
                levelNum--;
                gotoxy(MENUX1 + INCRX + (levelNum<<1), MENUY1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (joystickValue == 2 || keyboardValue == S) { //Down
            if (levelNum < 5) {
                gotoxy(MENUX1 + INCRX + (levelNum<<1), MENUY1 + INCRY);
                printf("  ");                   //Fjerner pilen
                levelNum++;
                gotoxy(MENUX1 + INCRX + (levelNum<<1), MENUY1 + INCRY);
                printf("<<");                   //Laver pilen
            }
        } else if (joystickValue == 8 || keyboardValue == D) { //Right - Select
            if (levelNum == 1) {
                gs->startlevel = levelNum;
            } else if (levelNum == 2) {
                gs->startlevel = levelNum;
            } else if (levelNum == 3) {
                gs->startlevel = levelNum;
            } else if (levelNum == 4){
                gs->startlevel = levelNum;
            } else {
                gs->startlevel = levelNum;
            }
            gs->currentlevel = gs->startlevel;
            playGame(gs);
        } else if (joystickValue == 4 || keyboardValue == A) { //Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseOptions(struct game_state_t* gs) {
    static uint8_t arrow = 1;
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
    printf("<<");
    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) { //Up
            if (arrow > 1){
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
                printf("  ");                   // Fjerner pilen
                arrow--;
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
                printf("<<");
            }                 // Laver pilen
        } else if (joystickValue == 2 || keyboardValue == S) { //Down
            if (arrow < 3){
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
                printf("  ");                   // Fjerner pilen
                arrow++;
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
                printf("<<");                   // Laver pilen
            }
        } else if (joystickValue == 8 || keyboardValue == D) { //Right - Select
            if (arrow == 1) {
                toggleMirror(gs);
            } else if (arrow == 2) {
                changeSpeed(gs);
            } else {
                changeNumberOfPlayers(gs);
            }
        } else if (joystickValue == 4 || keyboardValue == A) {//Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseHighscore(struct game_state_t* gs) {
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 4 || keyboardValue == A) {//Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseHelp(struct game_state_t* gs) {
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 4 || keyboardValue == A) {//Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseGameOver(struct game_state_t* gs){
    uint8_t arrow = 1;
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;
    int8_t i, j;

    //Sammenligner scoren med tidligere highscores
    for (i = 0; i < 5; i++){
        if (gs->points > gs->highscores[i]){
            for(j = 4; j >= i; j--){//Rykker tidligere highscores under den nye highscore én ned
                gs->highscores[j] = gs->highscores[j-1];
            }
            gs->highscores[i] = gs->points;  //Indsætter den nye highscore
            writeFlash(gs);
            break;
        }
    }
    gs->points = 0;//Resetter scoren efter et tabt spil

    drawGameOverWindow();
    gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
    printf("<<");
    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("  ");                   //Fjerner pilen
            arrow = 1;
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("<<");                   //Laver pilen
        } else if (joystickValue == 2 || keyboardValue == S) {
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("  ");                   //Fjerner pilen
            arrow = 2;
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("<<");                   //Laver pilen
        } else if (joystickValue == 8 || keyboardValue == D) {
            if (arrow == 1) {
                playGame(gs); //Loader det sidst tabte level
            } else {
                initDisplay(gs->buffer);
                chooseMenuOptions(gs); //Går til menuen og uploader scoren
            }
        }
    }
}

void chooseGameWon(struct game_state_t* gs){
    uint8_t arrow = 1;
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;
    int8_t i, j;

    //Sammenligner scoren med tidligere highscores
    for (i = 0; i < 5; i++){
        if (gs->points > gs->highscores[i]){
            for(j = 4; j >= i; j--){//Rykker tidligere highscores under den nye highscore én ned
                gs->highscores[j] = gs->highscores[j-1];
            }
            gs->highscores[i] = gs->points;  //Indsætter den nye highscore
            writeFlash(gs);
            break;
        }
    }
    gs->points = 0;//Resetter scoren efter et vundet spil


    drawGameWonWindow();
    gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
    printf("<<");
    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("  ");                   //Fjerner pilen
            arrow = 1;
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("<<");                   //Laver pilen
        } else if (joystickValue == 2 || keyboardValue == S) {
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("  ");                   //Fjerner pilen
            arrow = 2;
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("<<");                   //Laver pilen
        } else if (joystickValue == 8 || keyboardValue == D) {
            if (arrow == 1) {
                gs->currentlevel = gs->startlevel;
                playGame(gs); //Loader det level  man startede på
            } else {
                initDisplay(gs->buffer);
                chooseMenuOptions(gs); //Går til menuen og uploader scoren
            }
        }
    }
}

void toggleMirror(struct game_state_t* gs){
    static uint8_t mirrortoggle = 0;//Bruges til at sætte mode
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            gotoxy(30+INCRX+2,100+33);
            printf("   ");
            mirrortoggle = 1;
            gotoxy(30+INCRX+2,100+33);
            printf("On");
        } else if (joystickValue == 2 || keyboardValue == S) {
            mirrortoggle = 0;
            gotoxy(30+INCRX+2,100+33);
            printf("Off");
        } else if (joystickValue == 4 || keyboardValue == A) {
            gs->startmirror = mirrortoggle;
            chooseOptions(gs);
        }
    }
}

void changeSpeed(struct game_state_t* gs){
    static uint8_t difficulty = 1;//Bruges til at sætte hastighed
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            if (difficulty < 5){
                difficulty++;
                gotoxy(30+INCRX+4,100+34);
                printf("%d", difficulty);
            }
        } else if (joystickValue == 2 || keyboardValue == S) {
            if (difficulty > 1) {
                difficulty--;
                gotoxy(30+INCRX+4,100+34);
                printf("%d", difficulty);
            }
        } else if (joystickValue == 4 || keyboardValue == A) {
            gs->speed = difficulty;
            chooseOptions(gs);
        }
    }
}

void changeNumberOfPlayers(struct game_state_t* gs){
    static uint8_t playerNum = 1;//Bruges til at vælge antal spillerer
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            gotoxy(30+INCRX+6,100+33);
            printf("   ");
            playerNum = 2;
            gotoxy(30+INCRX+6,100+33);
            printf(" 2");
        } else if (joystickValue == 2 || keyboardValue == S) {
            playerNum = 1;
            gotoxy(30+INCRX+6,100+33);
            printf(" 1");
        } else if (joystickValue == 4 || keyboardValue == A) {
            gs->players = playerNum;
            chooseOptions(gs);
        }
    }
}
