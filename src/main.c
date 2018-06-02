#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include <string.h>
#include <stdio.h>
#include <time.h>

#include "ansi.h"
#include "LUT.h"
#include "struct.h"
#include "gamePhysics.h"

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a) * (b) >> FIX14_SHIFT )
#define FIX14_DIV(a ,b) ( ((a) << FIX14_SHIFT )

#define ESC 0x1B





int main(void)
    {
        init_usb_uart( 115200 ); // Initialize USB serial at 9600 baud
        struct ball_t bold;
        initbold(&bold,35,59);
        bold.dx=1;
        bold.dy=1;
        int32_t timer=0;
        int16_t counter=0;
        int8_t hit=0;
        int8_t x1=30,y1=30,x2=52,y2=88;

        clrscr();
        box(x1,y1,x2,y2,1);
        minibox(x1,y1,x2,y2,0, counter);
        drawball(&bold);

        while(1){
        if (++timer==100000ul){
            hit = checkEdge(&bold,x1,y1,x2,y2);
            counter += hit;
            minibox(30,30,52,88,0, counter);
            update(&bold, hit,x1 ,y1 ,x2 ,y2);
            drawball(&bold);
            timer=0;
        }
        if(counter > 255){
            break;
        }


        }



        while(1){}
}
