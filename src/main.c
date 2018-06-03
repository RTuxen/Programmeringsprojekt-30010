#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include <string.h>
#include <stdio.h>
#include <time.h>

#include "ansi.h"
#include "LUT.h"
#include "struct.h"
#include "gamePhysics.h"


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
        initbold(&bold,12,10,1,1);
        box(X1,Y1,X2,Y2,1);
        minibox(X1,Y1,X2,Y2,0, hitcounter);
        drawball(&bold);



	/***************************/
	/* Main Loop	           */
	/***************************/
        while(1){
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
