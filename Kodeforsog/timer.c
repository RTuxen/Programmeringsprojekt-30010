#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "struct.h"
#include "timer.h"

void initTimer100Hz(){
RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
 TIM2->CR1 = 0x0000; // Configure timer 2 - disabled
 TIM2->ARR = 0x00009C3F; // Set reload value to 39999
 TIM2->PSC = 0x000F; // Set prescale value to 15
 TIM2->CR1 = 0x0001; // Configure timer 2 - enabled
 TIM2->DIER |= 0x0001; // Enable timer 2 interrupts

 NVIC_SetPriority(TIM2_IRQn, 0000); // Set interrupt priority
 NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
}


void TIM2_IRQHandler(void){
    tid.centiseconds++;
    TIM2->SR &= ~0x0001; //Clear interrupt bit
}


void printTid(){
    uint8_t en;
    int8_t s,m,h;
    if (tid.centiseconds >= 100) {
        tid.seconds++;
        tid.centiseconds = 0;
        en = 1;

    }
    if (tid.seconds >= 60) {
        tid.minutes++;
        tid.seconds=0;
    }
    if (tid.minutes == 60) {
        tid.hours++;
        tid.minutes=0;
    }

 //   if (en) {

        NVIC_DisableIRQ(TIM2_IRQn);
        s = tid.seconds;
        m = tid.minutes;
        h = tid.hours;
        NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
        if (s < 10){
            printf("%d:%d:0%d", h, m, s);
        } else{
            printf("%d:%d:%d", h, m, s);
        }

        en = 0;
 //   }
}

void printSplit (int8_t c, int8_t s, int8_t m, int8_t h){
    printf("%d:%d:%d.%d", h, m, s,c);
}


void stopWatchControl(int8_t value){
    if (value == 16){ // Center - Stop/Start (enable and disable of clock)
        if (TIM2->CR1 & 0x0001){
            TIM2->CR1 = 0x0000;
        } else{
            TIM2->CR1 = 0x0001;
        }
    } else if (value == 4){ // Left - prints split 1
        NVIC_DisableIRQ(TIM2_IRQn);
        int8_t c = tid.centiseconds;
        int8_t s = tid.seconds;
        int8_t m = tid.minutes;
        int8_t h = tid.hours;
        NVIC_EnableIRQ(TIM2_IRQn);
        printSplit(c,s,m,h);
    } else if (value == 8){ // Right - Prints split 2
        NVIC_DisableIRQ(TIM2_IRQn);
        int8_t c = tid.centiseconds;
        int8_t s = tid.seconds;
        int8_t m = tid.minutes;
        int8_t h = tid.hours;
        NVIC_EnableIRQ(TIM2_IRQn);
        printSplit(c,s,m,h);
    } else if (value == 2){ // Down - Resets timer
        TIM2->CR1 = 0x0000;
        tid.centiseconds = 0;
        tid.seconds = 0;
        tid.minutes = 0;
        tid.hours = 0;
    }
}
