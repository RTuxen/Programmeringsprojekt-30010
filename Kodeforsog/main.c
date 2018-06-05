#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <string.h>

#include "ansi.h"
#include "LUT.h"
#include "struct.h"
#include "gamePhysics.h"
#include "IO.h"
#include "timer.h"


#define X1 1
#define Y1 1
#define X2 24
#define Y2 80

int main(void)
    {

    // Initialize terminal connection
    init_usb_uart( 115200 ); // Initialize USB serial at 9600 baud


    /***************************/
	/* Initialization          */
	/***************************/
        struct ball_t bold;
        int32_t timer=0;
        int16_t hitcounter=0;
        clrscr();


/*
        initbold(&bold,12,10,1,1);
        box(X1,Y1,X2,Y2,1);
        minibox(X1,Y1,X2,Y2,0, hitcounter);
        drawball(&bold);
*/






        initJoystick();
        initLED();
        initTimer100Hz();

        uint8_t k = 0;
        stopWatchWindow(10, 10, 15, 38, "Stop Watch", 1);
        int s = 0;
        while (0) {
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
	/* Main Loop	           */
	/***************************/
        while(0){
        if (++timer==130000ul){
            hitcounter += checkWallCollision(&bold,X1,Y1,X2,Y2);
            minibox(X1 ,Y1 ,X2 ,Y2 ,0, hitcounter);
            update(&bold,X1,Y1,X2,Y2);
            drawball(&bold);
            timer=0;
        }

        // Stops loop
        if(hitcounter > 255){
            break;
        }


        }



        while(1){}
}
