#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

//#include "menu.h"

#include "game.h"


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
        initTimer1000Hz();
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
	/* Stopwatch Joystick test */
	/***************************/
/*
        uint8_t k = 0;
        initJoystick();
        initTimer1000Hz();
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


//    clrscr();
//    while(1){
//        uint8_t k=readKeyboard();
//        if(k!= 0){
//            printf("%d\n",k);
//        }
//
//    }


//    initTimer1000Hz();//Initialiserer klokken TIM2
//    initJoystick();//Initialiserer joystick
//    init_spi_lcd();//Initialiserer LCD
//    initADC(); // Initialiserer Potentiometrene
//    initTimerPWM();
//    initBuzzer();
//    struct game_state_t gs;//Danner et game state struct
//    initGameState(&gs);//Initialisere game statet
//    clrscr();
//    hideCursor();
//    chooseMenuOptions(&gs);

    initTimer1000Hz();//Initialiserer klokken TIM2
    initJoystick();//Initialiserer joystick
    init_spi_lcd();//Initialiserer LCD
    initADC(); // Initialiserer Potentiometrene
    initTimerPWM();
    initBuzzer();
    struct game_state_t gs;//Danner et game state struct
    initGameState(&gs);//Initialisere game state_t
    backupDomainAccess();
    initRTC24(&gs.RTC_InitStruct);
    initTime(0x00, 0x10, 0x58, 0x45, &gs.RTC_TimeStruct);
    initDate(0x02, 0x19, 0x06, 0x18, &gs.RTC_DateStruct);
    clrscr();
    hideCursor();
    chooseMenuOptions(&gs);




        while(1){
        }
}






