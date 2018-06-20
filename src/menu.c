#include "menu.h"

void chooseMenuOptions(struct game_state_t* gs){
    uint8_t arrow = 1;
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;
    uint16_t t = tid.soundtime;
    static uint16_t i = 0;

    clrscr();
    inverse(0);
    underline(0);
    drawWelcomeMessage();
    setTimerDefault();
    drawMenuWindow();       // Draws Menu Window
    gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
    printf("<<");
    while(1) {
        /** Gets the input values */
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();

        if(tid.soundtime >= t+TETRIS_TEMPO[i]){ /** Plays tetris music */
                setFreq(TETRIS_MELODY[i]);
                t=tid.soundtime;
                i++;
                if(i >= 864){
                i=0;
            }
        }

        if (joystickValue == 1 || keyboardValue == W) {       // If joystick is pressed up, the arrow value is decremented, down to a minimum value, and the arrow is moved up to the previous line
            if (arrow > 1) {
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
                printf("  ");                   // Removes the arrow
                arrow--;
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
                printf("<<");                   // Draws the arrow
            }
        } else if (joystickValue == 2 || keyboardValue == S) {// If joystick is pressed down, the arrow value is incremented, up to a max value, and the arrow is moved down to the next line
            if (arrow < 4) {
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
                printf("  ");                   // Removes the arrow
                arrow++;
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + INCRY);
                printf("<<");                   // Draws the arrow
            }
        } else if (joystickValue == 8 || keyboardValue == D) {// If joystick is pressed to the right, the arrow value is used to choose
            setFreq(0); // Kills sound
            if (arrow == 1) {       //Play is chosen
                clrscr();
                drawPlayWindow();
                chooseLevel(gs);
            } else if (arrow == 2) { //Options is chosen
                clrscr();
                drawOptionMessage();
                drawOptionWindow(gs);
                chooseOptions(gs);
            } else if (arrow == 3) { //Highscorelist is chosen
                clrscr();
                drawHighscoreMessage();
                drawHighscoreWindow(gs);
                chooseHighscore(gs);
            } else {                // Help is chosen
                clrscr();
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
    uint16_t t = tid.soundtime;
    static uint8_t i = 0;

    gotoxy(MENUX1 + 2 + (levelNum<<1), MENUY1 + INCRY);
    printf("<<");
    while(1) {
        /** Gets the input values */
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();

        if(tid.soundtime >= t+UNDERWORLD_TEMPO[i]){ /** Plays Mario Underworld Theme */
            setFreq(UNDERWORLD_MELODY[i]);
            t=tid.soundtime;
            i++;
            if(i >= 57){
                i=0;
            }
        }

        if (joystickValue == 1 || keyboardValue == W) { //Up
            if (levelNum > 1) {
                gotoxy(MENUX1 + INCRX + (levelNum<<1), MENUY1 + INCRY);
                printf("  ");                   // Removes the arrow
                levelNum--;
                gotoxy(MENUX1 + INCRX + (levelNum<<1), MENUY1 + INCRY);
                printf("<<");                   // Draws the arrow
            }
        } else if (joystickValue == 2 || keyboardValue == S) { //Down
            if (levelNum < 5) {
                gotoxy(MENUX1 + INCRX + (levelNum<<1), MENUY1 + INCRY);
                printf("  ");                   // Removes the arrow
                levelNum++;
                gotoxy(MENUX1 + INCRX + (levelNum<<1), MENUY1 + INCRY);
                printf("<<");                   // Draws the arrow
            }
        } else if (joystickValue == 8 || keyboardValue == D) { //Right - Select
            setFreq(0); // Kills sound
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
    uint16_t t = tid.soundtime;
    static uint8_t i = 0;

    gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
    printf("<<");
    while(1) {
        /** Gets the input values */
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();

        if(tid.soundtime >= t+TEMPO[i]){ /** Plays Main Mario theme */
            setFreq(MELODY[i]);
            t=tid.soundtime;
            i++;
            if(i >= 81){
                i=0;
            }
        }

        if (joystickValue == 1 || keyboardValue == W) { //Up
            if (arrow > 1){
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
                printf("  ");                   // Removes the arrow
                arrow--;
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
                printf("<<");                   // Draws the arrow
            }
        } else if (joystickValue == 2 || keyboardValue == S) { //Down
            if (arrow < 4){
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
                printf("  ");                   // Removes the arrow
                arrow++;
                gotoxy(MENUX1 + INCRX + (arrow<<1), MENUY1 + 38);
                printf("<<");                   // Draws the arrow
            }
        } else if (joystickValue == 8 || keyboardValue == D) { // Right - Select
            setFreq(0);
            if (arrow == 1) {
                toggleMirror(gs);
            } else if (arrow == 2) {
                changeSpeed(gs);
            } else if (arrow == 3) {
                changeNumberOfPlayers(gs);
            } else {
                changeController(gs);
            }
        } else if (joystickValue == 4 || keyboardValue == A) {// Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseHighscore(struct game_state_t* gs) {
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        /** Gets the input values */
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 4 || keyboardValue == A) {// Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseHelp(struct game_state_t* gs) {
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        /** Gets the input values */
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 4 || keyboardValue == A) {// Left - Go back
            chooseMenuOptions(gs);
        }
    }
}

void chooseGameOver(struct game_state_t* gs){
    static uint8_t arrow = 1;
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;
    int8_t i, j, k = 0;

    clrscr();
    drawGameOverWindow();

    // Compares the score with the previous highscores
    for (i = 0; i < 5; i++){
        if (gs->points > gs->highscores[i]){
            for(j = 4; j >= i; j--){ // Moves previous highscores, under the new highscore, one row down
                gs->highscores[j] = gs->highscores[j-1]; // Shifts the scores once
                memset(gs->highscorenames[j], 0x00, 14); // Makes sure there's no left overs of the previous name
                for (k = 0; k < 7; k++){
                    gs->highscorenames[j][k] = gs->highscorenames[j-1][k];
                }

                gs->highscoreMinutes[j] = gs->highscoreMinutes[j-1];
                gs->highscoreHours[j] = gs->highscoreHours[j-1];
                gs->highscoreDate[j] = gs->highscoreDate[j-1];
                gs->highscoreMonth[j] = gs->highscoreMonth[j-1];
            }

            //Inserts new highscore
            gs->highscores[i] = gs->points;

            inverse(1);
            gotoxy(MENUX1+14, MENUY1+7);
            printf("Write your name (6 characters): ");

            // Gets the player name
            k = 0;
            underline(1);
            while(k < 6 && gs->highscorenames[i][k-1] != 0x0D){

                gs->highscorenames[i][k]=(uint16_t)uart_getc();
                if (gs->highscorenames[i][k] == 0x7F){// Checks for backspace
                    k -= 2;
                }
                k++;
            }
            underline(0);
            inverse(0);
            gs->highscorenames[i][k] = 0x00; // Ends with a \0

            // Gets the time and date
            RTC_GetTime(RTC_Format_BIN, &gs->RTC_TimeStruct);
            RTC_GetDate(RTC_Format_BIN, &gs->RTC_DateStruct);

            // Inserts the time and date
            gs->highscoreMinutes[i] = gs->RTC_TimeStruct.RTC_Minutes;
            gs->highscoreHours[i] = gs->RTC_TimeStruct.RTC_Hours;
            gs->highscoreDate[i] = gs->RTC_DateStruct.RTC_Date;
            gs->highscoreMonth[i] = gs->RTC_DateStruct.RTC_Month;

            writeFlash(gs);
            break;
        }
    }
    gs->points = 0;//Resets the score after a lost game

    gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
    printf("<<");
    while(1) {
        /** Gets the input values */
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("  ");                   // Removes the arrow
            arrow = 1;
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("<<");                   // Draws the arrow
        } else if (joystickValue == 2 || keyboardValue == S) {
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("  ");                   // Removes the arrow
            arrow = 2;
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("<<");                   // Draws the arrow
        } else if (joystickValue == 8 || keyboardValue == D) {
            if (arrow == 1) {
                playGame(gs); // Loads the start level
            } else {
                initDisplay(gs->buffer); // Clears the LCD
                chooseMenuOptions(gs); // Goes to the main menu
            }
        }
    }
}

void chooseGameWon(struct game_state_t* gs){
    static uint8_t arrow = 1;
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;
    int8_t i, j, k = 0;

    clrscr();
    drawTrophy();
    drawGameWonWindow();

    // Compares the score with the previous highscores
    for (i = 0; i < 5; i++){
        if (gs->points > gs->highscores[i]){
            for(j = 4; j >= i; j--){// Moves previous highscores, under the new highscore, one row down
                gs->highscores[j] = gs->highscores[j-1];
                memset(gs->highscorenames[j], 0x00, 14); // Makes sure there's no left overs of the previous name
                for (k = 0; k < 7; k++){
                    gs->highscorenames[j][k] = gs->highscorenames[j-1][k];
                }

                gs->highscoreMinutes[j] = gs->highscoreMinutes[j-1];
                gs->highscoreHours[j] = gs->highscoreHours[j-1];
                gs->highscoreDate[j] = gs->highscoreDate[j-1];
                gs->highscoreMonth[j] = gs->highscoreMonth[j-1];
            }

            // Inserts new highscore
            gs->highscores[i] = gs->points;

            // Asks for the player name
            gotoxy(MENUX1+14, MENUY1+14);
            inverse(1);
            printf("Write your 6 chars: ");

            // Gets the player name
            k = 0;
            underline(1);
            while(k < 6 && gs->highscorenames[i][k-1] != 0x0D){

                gs->highscorenames[i][k]=(uint16_t)uart_getc();
                if (gs->highscorenames[i][k] == 0x7F){ // Checks for backspace
                    k -= 2;
                }
                k++;
            }
            underline(0);
            inverse(0);
            gs->highscorenames[i][k] = 0x00; // Ends with a \0

            // Gets the time and date
            RTC_GetTime(RTC_Format_BIN, &gs->RTC_TimeStruct);
            RTC_GetDate(RTC_Format_BIN, &gs->RTC_DateStruct);

            // Inserts the time and date
            gs->highscoreMinutes[i] = gs->RTC_TimeStruct.RTC_Minutes;
            gs->highscoreHours[i] = gs->RTC_TimeStruct.RTC_Hours;
            gs->highscoreDate[i] = gs->RTC_DateStruct.RTC_Date;
            gs->highscoreMonth[i] = gs->RTC_DateStruct.RTC_Month;

            writeFlash(gs);
            break;
        }
    }
    gs->points = 0;// Resets the score after a won game

    // Now you can go up, down and select your next option
    gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
    printf("<<");
    while(1) {
        // Gets the input values
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("  ");                   // Removes the arrow
            arrow = 1;
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("<<");                   // Draws the arrow
        } else if (joystickValue == 2 || keyboardValue == S) {
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("  ");                   // Removes the arrow
            arrow = 2;
            gotoxy(MENUX1 + INCRX + 2 + (arrow<<1), MENUY1 + 35);
            printf("<<");                   // Draws the arrow
        } else if (joystickValue == 8 || keyboardValue == D) {
            if (arrow == 1) {
                playGame(gs); // Loads the start level
            } else {
                initDisplay(gs->buffer); // Clears the LCD
                chooseMenuOptions(gs); // Goes to the main menu
            }
        }
    }
}

void toggleMirror(struct game_state_t* gs){
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        // Gets the input values
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            gotoxy(30+INCRX+2,100+33);
            printf("   ");          // Removes Off
            gs->startmirror = 1;
            gotoxy(30+INCRX+2,100+33);
            printf("On");
        } else if (joystickValue == 2 || keyboardValue == S) {
            gs->startmirror = 0;
            gotoxy(30+INCRX+2,100+33);
            printf("Off");
        } else if (joystickValue == 4 || keyboardValue == A) {
            chooseOptions(gs);
        }
    }
}

void changeSpeed(struct game_state_t* gs){
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        // Gets the input values
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            if (gs->speed < 5){
                gs->speed++;
                gotoxy(30+INCRX+4,100+34);
                printf("%d", gs->speed);
            }
        } else if (joystickValue == 2 || keyboardValue == S) {
            if (gs->speed > 1) {
                gs->speed--;
                gotoxy(30+INCRX+4,100+34);
                printf("%d", gs->speed);
            }
        } else if (joystickValue == 4 || keyboardValue == A) {
            chooseOptions(gs);
        }
    }
}

void changeNumberOfPlayers(struct game_state_t* gs){
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        // Gets the input values
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            gs->players = 2;
            gotoxy(30+INCRX+6,100+33);
            printf(" 2");
        } else if (joystickValue == 2 || keyboardValue == S) {
            gs->players = 1;
            gotoxy(30+INCRX+6,100+33);
            printf(" 1");
        } else if (joystickValue == 4 || keyboardValue == A) {
            chooseOptions(gs);
        }
    }
}

void changeController(struct game_state_t* gs){
    uint8_t joystickValue = 0;
    uint8_t keyboardValue = 0;

    while(1) {
        // Gets the input values
        joystickValue = readJoyStick();
        keyboardValue = readKeyboard();
        if (joystickValue == 1 || keyboardValue == W) {
            gotoxy(30+INCRX+8,100+33);
            printf("   ");          // Removes Off
            gs->I2C_Active = 1;
            gotoxy(30+INCRX+8,100+33);
            printf("On");
        } else if (joystickValue == 2 || keyboardValue == S) {
            gs->I2C_Active = 0;
            gotoxy(30+INCRX+8,100+33);
            printf("Off");
        } else if (joystickValue == 4 || keyboardValue == A) {
            chooseOptions(gs);
        }
    }
}
