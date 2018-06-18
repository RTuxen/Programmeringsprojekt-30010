#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "menu.h"
#include "rtc.h"


int main(void)
    {

    // Initialize terminal connection
    init_usb_uart( 115200 ); // Initialize USB serial at 9600 baud

    //Calls the structs needed
    RTC_InitTypeDef RTC_InitStruct;
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;

    // Gets Backup Domain Access, selects clock source and enables the RTC
    backupDomainAccess();

    //Initializes the RTC prescaler and hour format
    RTC_StructInit(&RTC_InitStruct);
    RTC_Init(&RTC_InitStruct);

    // Sets Time to 00h:00min:00sec
    RTC_TimeStructInit(&RTC_TimeStruct);
    gotoxy(10,1);
    printf("%c", RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct));

    // Sets date to Monday, January 01 xx00
    RTC_DateStructInit(&RTC_DateStruct);
    RTC_SetDate(RTC_Format_BCD, &RTC_DateStruct);

    // Gets the time and date
    RTC_GetTime(RTC_Format_BCD, &RTC_TimeStruct);
    RTC_GetDate(RTC_Format_BCD, &RTC_DateStruct);

    // Clears and checks for RSF flag
    RTC_WaitForSynchro();

    // Prints the values
    gotoxy(1,1);
    printf("Hours = %d\n", RTC_TimeStruct.RTC_Hours);
    printf("Minutes = %d\n", RTC_TimeStruct.RTC_Minutes);
    printf("Seconds = %d\n", RTC_TimeStruct.RTC_Seconds);
    printf("Weekday = %d\n", RTC_DateStruct.RTC_WeekDay);
    printf("Month = %d\n", RTC_DateStruct.RTC_Month);
    printf("Date = %d\n", RTC_DateStruct.RTC_Date);
    printf("Year = %d\n", RTC_DateStruct.RTC_Year);
    while (1){
    }

//    struct RTC_Init_t RTC_InitStruct;
//    RTC_StructInit(&RTC_InitStruct);
//    RTC_Init(&RTC_InitStruct);
//
//    // Sets Time to 00h:00min:00sec
//    struct RTC_Time_t RTC_TimeStruct;
//    RTC_TimeStructInit(&RTC_TimeStruct);
//    RTC_SetTime(&RTC_TimeStruct);
//
//    // Sets date to Monday, January 01 xx00
//    struct RTC_Date_t RTC_DateStruct;
//    RTC_DateStructInit(&RTC_DateStruct);
//    RTC_SetDate(&RTC_DateStruct);



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
//    gotoxy(10,10);
//
//    while(1){
//
//        if(readKeyboard() == 32){
//            printf("HEJ\n");
//
//        }
//    }



    initTimer100Hz();//Initialiserer klokken TIM2
    initJoystick();//Initialiserer joystick
    init_spi_lcd();//Initialiserer LCD
    initADC(); // Initialiserer Potentiometrene
    struct game_state_t gs;//Danner et game state struct
    initGameState(&gs);//Initialisere game statet
    clrscr();
    hideCursor();
    chooseMenuOptions(&gs);



        while(1){
        }
}






