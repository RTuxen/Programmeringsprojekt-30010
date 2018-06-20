#include "graphics.h"

uint8_t strlens(char* text) { // Calculate the length of a string
	uint8_t length = 0;
	while(*text++ != '\0')
		length++;
	return length;
}

void window (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char str[]){ // Draws window with text in the middle
    uint8_t len = strlens(str);
    uint8_t i, j;
    uint8_t dx = x2-x1;
    uint8_t dy = y2-y1;


    if (x1 >= x2 || y1 >= y2 || len > dy-2){
        return;
    }

    int8_t incre = dy/2 - len/2;
    gotoxy(x1, y1);

    for (i = 1; i <= dx; i++){
        if (i == 1) {       // Draws the upper left corner
            printf("%c", 201);
        } else if(i == dx){   // Draws the lower left corner
            printf("%c", 200);
        } else{             // Draws the line on the right
            printf("%c", 186);
            moveCursor('C', dy);
        }
        for (j = 1; j <= dy; j++){
            if (i == 1){ // Draws at the first line
                if (j < incre){
    				printf("%c", 205);
    			} else if (j == incre) {
                    printf("%c", 185);
                } else if ( j - 1 - incre < len){ // Draws the string
                    inverse(1);
                    printf("%c",str[j - 1 - incre]);
                    inverse(0);
                } else if (j - 1 - incre == len){
                    printf("%c", 204);
                } else {
                    printf("%c", 205);
                }
            } else if (i == dx) { // Draws the last line
                printf("%c", 205);
            }
        }
        if (i == 1) {         // Draws the upper right corner
            printf("%c", 187);
        } else if(i == dx){   // Draws the lower right corner
            printf("%c", 188);
        } else{             // Draws the line on the right
            printf("%c", 186);
        }
        gotoxy(x1+i,y1);
    }
}

void drawWalls (){ // Draws walls
    uint16_t i, j;
    uint16_t dx = X2-X1+1;
    uint16_t dy = Y2-Y1;

    fgcolor(6); // Sets color to cyan

    if (X1 >= X2 || Y1 >= Y2){
        return;
    }
    // Goes to the starting point
    gotoxy(X1,Y1-1);
    // Draws the upper left corner
    printf("%c%c", 219, 219);
    // Draws the upper line
    for ( j=1; j<=dy; j++){
        printf("%c",219);
    }
    // Draws the upper right corner
    printf("%c%c", 219, 219);
    for (i = 1; i <= dx; i++){
        // Goes to the next line at the chosen y-value
        gotoxy(X1+i,Y1-1);
        // Draws the line on the left
        printf("%c%c", 219, 219);
        // Moves to the right
        moveCursor('C', dy);
        // Draws the line on the right
        printf("%c%c", 219, 219);
    }
}

void drawball(struct ball_t * ball){
    fgcolor(15);
    gotoxy(ball->x >> 14,ball->y >> 14);
    printf("O");
}

void drawPlayer(struct player_t *striker){
    fgcolor(15);
    gotoxy(striker->x,striker->y-7);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);

}

void drawBlock(struct block_t block) { // Each block is 15 wide and 2 high

	if (block.lives >= 0) {
		gotoxy(block.x, block.y);

		if (block.lives == 0) { // Delete block if it has no lives left.
			fgcolor(0);
			printf("               ");
			gotoxy(block.x+1,block.y);
			printf("               ");
		} else if (block.lives == 1) { // Draws block depending on lives.
			fgcolor(9);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176);
			gotoxy(block.x+1,block.y);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176);
		} else if (block.lives == 2) {
			fgcolor(10);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			gotoxy(block.x+1,block.y);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
		} else if (block.lives == 3) {
			fgcolor(7);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			gotoxy(block.x+1,block.y);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
		} else {
			fgcolor(4);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			gotoxy(block.x+1,block.y);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
		}
	}

	gotoxy(0, 0);
}

void drawBlockMap(struct block_t *bricks){
    uint8_t i;
    for (i = 0; i < 32; i++) {
            drawBlock(bricks[i]); // Draw blocks
        }
}

void printfallObject(struct fallingObject_t *fallObject){ // Draws powerup
    if (fallObject->type){
        if (fallObject->type==1){
            fgcolor(1);
        } else if(fallObject->type==2){
            fgcolor(2);
        } else if(fallObject->type==3){
            fgcolor(3);
        } else if(fallObject->type == 4){
            fgcolor(4);
        }
        gotoxy(fallObject->x, fallObject->y);
        printf("%c",219);
    }
}

void drawMenuWindow() { /**MAIN MENU WINDOW */
    char str[] = " Menu ";
    fgcolor(15);

    window(MENUX1, MENUY1, MENUX2, MENUY2, str);
    gotoxy(MENUX1+INCRX+2,MENUY1+10);
    printf("Play");
    gotoxy(MENUX1+INCRX+4,MENUY1+10);
    printf("Options");
    gotoxy(MENUX1+INCRX+6,MENUY1+10);
    printf("Highscore");
    gotoxy(MENUX1+INCRX+8,MENUY1+10);
    printf("Help");
}

void drawPlayWindow() { /**PLAY MENU WINDOW */
    char str[] = " Level ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str);
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

void drawOptionWindow(struct game_state_t* gs) { /**OPTIONS MENU WINDOW */
    char str[] = " Options ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str);
    gotoxy(MENUX1+INCRX+2,MENUY1+20);
    if (gs->startmirror){
        printf("Mirrormode:  On");
    } else {
        printf("Mirrormode:  Off");
    }
    gotoxy(MENUX1+INCRX+4,MENUY1+20);
    printf("Speed:        %d", gs->speed);
    gotoxy(MENUX1+INCRX+6,MENUY1+20);
    printf("Players:      %d",gs->players);
    gotoxy(MENUX1+INCRX+8,MENUY1+20);
    if (gs->I2C_Active){
        printf("AccMeter:    On");
    } else {
        printf("AccMeter:    Off");
    }
}

void drawHelpWindow() { /**HELP MENU WINDOW */
    char str[] = " Help ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str);

    /**Game controls */
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

void drawGameOverWindow() { /**GAME OVER WINDOW */
    char str[] = " Game Over ";
    fgcolor(15); // White

    window(MENUX1, MENUY1, MENUX2, MENUY2, str);
    gotoxy(MENUX1+INCRX+2,MENUY1+20);
    printf("YOU DIED !");
    gotoxy(MENUX1+INCRX+4,MENUY1+20);
    printf("Play again?");
    gotoxy(MENUX1+INCRX+6,MENUY1+20);
    printf("Go to Menu");
}

void drawGameWonWindow(){ /**GAME WON WINDOW */
    char str[] = " Game Won ";

    drawTrophy();
    window(MENUX1, MENUY1, MENUX2, MENUY2, str);
    gotoxy(MENUX1+INCRX+2,MENUY1+17);
    printf("YOU WON... THIS TIME");
    gotoxy(MENUX1+INCRX+4,MENUY1+20);
    printf("Play again?");
    gotoxy(MENUX1+INCRX+6,MENUY1+20);
    printf("Go to Menu");
}

void drawHighscoreWindow(struct game_state_t* gs) { /**Draws list of highscores with all required information */
    char str[] = " Highscores ";

    window(MENUX1, MENUY1, MENUX2, MENUY2, str);
    //Highscorelist - Writes place, score, name, date, month, hours and minutes
    gotoxy(MENUX1+INCRX+2,MENUY1+10);
    underline(1);
    printf("Highscores");
    underline(0);
    gotoxy(MENUX1+INCRX+4,MENUY1+15);
    printf("1. %3d ", gs->highscores[0]);
    writeScoreName(gs, 0);
    printf(" %02d/%02d %02d:%02d", gs->highscoreDate[0], gs->highscoreMonth[0], gs->highscoreHours[0], gs->highscoreMinutes[0]);

    gotoxy(MENUX1+INCRX+6,MENUY1+15);
    printf("2. %3d ", gs->highscores[1]);
    writeScoreName(gs, 1);
    printf(" %02d/%02d %02d:%02d", gs->highscoreDate[1], gs->highscoreMonth[1], gs->highscoreHours[1], gs->highscoreMinutes[1]);

    gotoxy(MENUX1+INCRX+8,MENUY1+15);
    printf("3. %3d ", gs->highscores[2]);
    writeScoreName(gs, 2);
    printf(" %02d/%02d %02d:%02d", gs->highscoreDate[2], gs->highscoreMonth[2], gs->highscoreHours[2], gs->highscoreMinutes[2]);

    gotoxy(MENUX1+INCRX+10,MENUY1+15);
    printf("4. %3d ", gs->highscores[3]);
    writeScoreName(gs, 3);
    printf(" %02d/%02d %02d:%02d", gs->highscoreDate[3], gs->highscoreMonth[3], gs->highscoreHours[3], gs->highscoreMinutes[3]);

    gotoxy(MENUX1+INCRX+12,MENUY1+15);
    printf("5. %3d ", gs->highscores[4]);
    writeScoreName(gs, 4);
    printf(" %02d/%02d %02d:%02d", gs->highscoreDate[4], gs->highscoreMonth[4], gs->highscoreHours[4], gs->highscoreMinutes[4]);
}

void writeScoreName(struct game_state_t* gs, uint8_t n){ /** Writes the highscore name of the n+1 place. **/
    uint8_t i;
    underline(1);
    for (i = 0; i < 6; i++){
        if (gs->highscorenames[n][i]  == 0x0D){
            printf(" ");
        } else if (gs->highscorenames[n][i]) {
            printf("%c", gs->highscorenames[n][i]);
        } else {
            printf(" ");
        }
    }
    underline(0);
}

void drawWelcomeMessage(){
    gotoxy(21,85);
    printf(" _    _      _                            _           ___       _                     _     _ ");
    gotoxy(22,85);
    printf("| |  | |    | |                          | |         / _ \\     | |                   (_)   | |");
    gotoxy(23,85);
    printf("| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___   / /_\\ \\_ __| | ____ _ _ __   ___  _  __| |");
    gotoxy(24,85);
    printf("| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  |  _  | '__| |/ / _` | '_ \\ / _ \\| |/ _` |");
    gotoxy(25,85);
    printf("\\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | | | | |  |   < (_| | | | | (_) | | (_| |");
    gotoxy(26,85);
    printf(" \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/  \\_| |_/_|  |_|\\_\\__,_|_| |_|\\___/|_|\\__,_|");

}

void drawOptionMessage(){
    gotoxy(21,109);
    printf(" _____       _   _                 ");
    gotoxy(22,109);
    printf("|  _  |     | | (_)                ");
    gotoxy(23,109);
    printf("| | | |_ __ | |_ _  ___  _ __  ___ ");
    gotoxy(24,109);
    printf("| | | | '_ \\| __| |/ _ \\| '_ \\/ __|");
    gotoxy(25,109);
    printf("\\ \\_/ / |_) | |_| | (_) | | | \\__ \\");
    gotoxy(26,109);
    printf(" \\___/| .__/ \\__|_|\\___/|_| |_|___/");
    gotoxy(27,109);
    printf("      | |                          ");
    gotoxy(28,109);
    printf("      |_|                          ");

}

void drawHighscoreMessage(){
    gotoxy(21,101);
    printf(" _   _ _       _                                 ");
    gotoxy(22,101);
    printf("| | | (_)     | |                                ");
    gotoxy(23,101);
    printf("| |_| |_  __ _| |__  ___  ___ ___  _ __ ___  ___ ");
    gotoxy(24,101);
    printf("|  _  | |/ _` | '_ \\/ __|/ __/ _ \\| '__/ _ \\/ __|");
    gotoxy(25,101);
    printf("| | | | | (_| | | | \\__ \\ (_| (_) | | |  __/\\__ \\");
    gotoxy(26,101);
    printf("\\_| |_/_|\\__, |_| |_|___/\\___\\___/|_|  \\___||___/");
    gotoxy(27,101);
    printf("          __/ |                                  ");
    gotoxy(28,101);
    printf("         |___/                                   ");

}

void drawHelpMessage(){
    gotoxy(21, 117);
    printf(" _   _      _       ");
    gotoxy(22, 117);
    printf("| | | |    | |      ");
    gotoxy(23, 117);
    printf("| |_| | ___| |_ __  ");
    gotoxy(24, 117);
    printf("|  _  |/ _ \\ | '_ \\ ");
    gotoxy(25, 117);
    printf("| | | |  __/ | |_) |");
    gotoxy(26, 117);
    printf("\\_| |_/\\___|_| .__/ ");
    gotoxy(27, 117);
    printf("             | |    ");
    gotoxy(28, 117);
    printf("             |_|    ");

}

void drawTrophy(){
    gotoxy(30,80);
    printf(" .-=========-.");
    gotoxy(31,80);
    printf(" \'-=======-'/");
    gotoxy(32,80);
    printf(" _|   .=.   |_");
    gotoxy(33,80);
    printf("((|  {{1}}  |))");
    gotoxy(34,80);
    printf(" \\|   /|\\   |/ ");
    gotoxy(35,80);
    printf("  \\__ '`' __/  ");
    gotoxy(36,80);
    printf("    _`) (`_    ");
    gotoxy(37,80);
    printf("  _/_______\\_  ");
    gotoxy(38,80);
    printf(" /___________\\ ");

}
