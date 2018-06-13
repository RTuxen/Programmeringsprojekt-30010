#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <string.h>

#include "ansi.h"
#include "LUT.h"
#include "struct.h"
#include "gamePhysics.h"
#include "IO.h"
#include "timer.h"
#include "display.h"
#include "charset.h"
#include "graphics.h"
#include "menu.h"
#include "levels.h"



int main(void)
    {

    // Initialize terminal connection
    init_usb_uart( 115200 ); // Initialize USB serial at 9600 baud


    /***************************/
	/* Initialization          */
	/***************************/





    /***************************/
	/* LCD slideshow test      */
	/***************************/
/*
        uint8_t buffer[512];
        initTimer100Hz();
        initDisplay(buffer);
        lcd_write_string(buffer,"HEJ MED oasd k ei jfj ud ke jd", 2, 0);
        lcd_write_string(buffer,"HEJ MED oasd k ei jfj ud ke jd", 2, 1);
        lcd_write_string(buffer,"HEJ MED oasd k ei jfj ud ke jd", 2, 2);
        lcd_write_string(buffer,"Hokay", 2, 3);

        initADC();
        while(1) {
            lcd_updateline(buffer, 3);
        }
*/




    /***************************/
	/* LCD - Dreje håndtag     */
	/***************************/
 /*   uint16_t val1, val2;
    uint8_t buffer[512];
    char str1[30], str2[30];
    initADC();
    initDisplay(buffer);
    while (0) {
        val1 = readADC_pa0();
        val2 = readADC_pa1();
        sprintf(str1, "Value 1 = %4d", val1);
        sprintf(str2, "Value 2 = %4d", val2);
        lcd_write_string(buffer, str1, 1, 0);
        lcd_write_string(buffer, str2, 1, 1);
    }
*/


	/***************************/
	/* Stopwatch Joystick test */
	/***************************/
/*
        uint8_t k = 0;
        initJoystick();
        initTimer100Hz();
        clrscr();
        stopWatchWindow(10, 10, "Stop Watch", 1);
        int s = 0;
        while (1) {
            if (s == tid.seconds){
            gotoxy(11,30);
            printTid();
            if (k != readJoyStick()){
                k = readJoyStick();
                setLed(k);
                if (k == 4) {
                    gotoxy(12,30);
                    stopWatchControl(readJoyStick());
                } else if (k == 8){
                    gotoxy(13,30);
                    stopWatchControl(readJoyStick());
                } else if (k == 16){
                    gotoxy(11,30);
                    printf("0:0:00");
                    stopWatchControl(readJoyStick());
                } else if(k == 2){
                    stopWatchControl(readJoyStick());
                }

            }
            s = tid.seconds;
            }
        }
*/

	/***************************/
	/* Stopwatch keyboard test */
	/***************************/
/*
    gotoxy(20,0);
    saveCursor();
        while (1) {
            gotoxy(11,30);
            printTid();
            getSavedCursor();
            printf("\n");
            textReturn(20);
            printf("\n");
            saveCursor();

        }

*/


	/***************************/
	/* Joystick LED test	   */
	/***************************/
 /*
        initJoystick();
        initLED();
        gotoxy(25,2);
        int i=1;
        int8_t k = 0;
        while(1){

            if (k != readJoyStick()){
                k = readJoyStick();
                setLed(k);
                if (k) {
                    printf("%d",readJoyStick());
                    gotoxy(25+i,2);
                    i++;
                }
            }
        }
*/

    /***************************/
	/* Full Box Loop	       */
	/***************************/
/*
        struct ball_t bold;
        struct player_t striker;
        int32_t timerCount=0;
        int16_t hitcounter=0;
        clrscr();

        initbold(&bold,12,10,1,1);
        initPlayer(&striker,37,58);
        initJoystick();
        box(X1,Y1,X2,Y2,1);
        minibox(X1,Y1,X2,Y2,0, hitcounter);
        drawball(&bold);
        drawPlayer(&striker);
        gotoxy(50,0);

        while(1){
        if (++timerCount==130000ul){
            hitcounter += checkWallCollision(&bold,X1,Y1,X2,Y2);
            minibox(X1 ,Y1 ,X2 ,Y2 ,0, hitcounter);
            updatePlayerPos(&striker);
            updateBallPos(&bold,&striker,X1,Y1,X2,Y2);
            timerCount=0;
        }

        // Stops loop
        if(hitcounter > 255){
            break;
        }


        }
*/

    /***************************/
    /* LCD - Striker Points    */
    /***************************/
/*
    uint16_t val1, val2, val3;
    struct player_t striker;
    striker.level = 3;
    striker.lifes = 10;
    striker.points = 50;
    uint8_t buffer[512];
    char str1[30], str2[30], str3[30];
    initADC();
    initDisplay(buffer);
    while (1) {
        val1 = striker.level;
        val2 = striker.points;
        val3 = striker.lifes;
        sprintf(str1, "Level  = %4d", val1);
        sprintf(str2, "Points = %4d", val2);
        sprintf(str3, "Lifes  = %4d", val3);

        lcd_write_string(buffer, str1, 1, 0);
        lcd_write_string(buffer, str2, 1, 1);
        lcd_write_string(buffer, str3 , 2, 2);
   }
*/


	/***************************/
	/* Main Loop	           */
	/***************************/


//        initJoystick();
//        fgcolor(15);
//        clrscr();
//        while(1){
//            chooseMenuOptions();
//        }

//        uint8_t score = 8;
//        initJoystick();
//        fgcolor(15);
//        clrscr();
//        while(1){
//            //chooseMenuOptions(score);
//            chooseGameOver(score);
//        }
    initTimer100Hz();//Initialisere klokken TIM2
    initJoystick();//Initialisere joystick
    init_spi_lcd();//Initialisere LCD
    struct game_state_t gs;//Danner et game state struct
    initGameState(&gs);//Initialisere game statet
    clrscr();
    hideCursor();
    chooseMenuOptions(&gs);

//    struct game_state_t gs;
//    chooseMenuOptions(&gs);

//        struct ball_t bold;
//        struct player_t striker;
//        struct level_t bane;
//        int32_t timerCount=0;
//        int16_t slut=0;
//
//        initTimer100Hz();
//        initLevel(&bold,&striker,&bane);
//
//        static uint8_t buffer[512];
//        initDisplay(buffer);
//
//
//        while(1){
//            if (++timerCount==100000ul){
//                updatePlayerPos(&striker);
//                slut = updateBallPos(&bold,&striker,&bane);
//                if (slut){
//                    chooseGameOver(striker.points);
//                }
//                timerCount=0;
//
//                LCD_Printer(striker.level,striker.lifes,striker.points, buffer);
//            }
//        }

//        while(1){
//                if (get_game_flag()){
//                    updatePlayerPos(&striker);
//                    slut = updateBallPos(&bold,&striker,&bane);
//                    if (slut){
//                        chooseGameOver(striker.points);
//                    }
//                }
//        }


        while(1){
        }
}


