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
#include "rtc.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int main(void)
    {

    // Initialize terminal connection
    init_usb_uart(115200); // Initialize USB serial at 9600 baud

    clrscr();
    //Calls the structs needed
    RTC_InitTypeDef RTC_InitStruct;
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;

    // Gets Backup Domain Access, selects clock source and enables the RTC
    backupDomainAccess();

    //Initializes the RTC prescaler and hour format
    RTC_StructInit(&RTC_InitStruct);
//    RTC_Init(&RTC_InitStruct);
//    RTC_WriteProtectionCmd(DISABLE);
//    RTC_EnterInitMode();

    // Disables write protection
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    gotoxy(8,1);
    if (RTC_EnterInitMode() == ERROR){
        printf("ERRORinit");
    } else {
        printf("SUCCESinit");
    }

    gotoxy(9,1);
    if (RTC_Init(&RTC_InitStruct) == ERROR){
        printf("ERRORstruct");
    } else {
        printf("SUCCESstruct");
    }

    // Sets Time to 00h:00min:00sec
//    RTC_TimeStructInit(&RTC_TimeStruct);
    initTime(0x00, 0x11, 0x15, 0x30, &RTC_TimeStruct);
    gotoxy(10,1);
    if (RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct) == ERROR){
        printf("ERRORtime");
    } else {
        printf("SUCCEStime");
    }

    // Sets date to Monday, January 01 xx00
    RTC_DateStructInit(&RTC_DateStruct);
    RTC_SetDate(RTC_Format_BCD, &RTC_DateStruct);

    // Clears and checks for RSF flag
    RTC_WaitForSynchro();

    while (1){
    // Gets the time and date
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);

    // Prints the values
    gotoxy(1,1);
    printf("Hours = %d\n",  RTC_TimeStruct.RTC_Hours);
    printf("Minutes = %d\n", RTC_TimeStruct.RTC_Minutes);
    printf("Seconds = %d\n", RTC_TimeStruct.RTC_Seconds);
    printf("Weekday = %d\n", RTC_DateStruct.RTC_WeekDay);
    printf("Month = %d\n", RTC_DateStruct.RTC_Month);
    printf("Date = %d\n", RTC_DateStruct.RTC_Date);
    printf("Year = %d\n", RTC_DateStruct.RTC_Year);
    }
    while (1){
    }

//  uint16_t  melody[] = {
//  NOTE_E7, NOTE_E7, 0, NOTE_E7,
//  0, NOTE_C7, NOTE_E7, 0,
//  NOTE_G7, 0, 0,  0,
//  NOTE_G6, 0, 0, 0,
//
//  NOTE_C7, 0, 0, NOTE_G6,
//  0, 0, NOTE_E6, 0,
//  0, NOTE_A6, 0, NOTE_B6,
//  0, NOTE_AS6, NOTE_A6, 0,
//
//  NOTE_G6, NOTE_E7, NOTE_G7,
//  NOTE_A7, 0, NOTE_F7, NOTE_G7,
//  0, NOTE_E7, 0, NOTE_C7,
//  NOTE_D7, NOTE_B6, 0, 0,
//
//  NOTE_C7, 0, 0, NOTE_G6,
//  0, 0, NOTE_E6, 0,
//  0, NOTE_A6, 0, NOTE_B6,
//  0, NOTE_AS6, NOTE_A6, 0,
//
//  NOTE_G6, NOTE_E7, NOTE_G7,
//  NOTE_A7, 0, NOTE_F7, NOTE_G7,
//  0, NOTE_E7, 0, NOTE_C7,
//  NOTE_D7, NOTE_B6, 0, 0
//};
//
//uint8_t tempo[] = {
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//  12, 12, 12, 12,
//};
//
//    initTimer100Hz();
//    initTimerPWM();
//    initBuzzer();
//    while(1){
//        load_sound(melody, tempo);
//    }


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


