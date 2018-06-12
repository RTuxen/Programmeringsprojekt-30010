#include "timer.h"

volatile uint8_t flag = 0;      //Flag til LCD update
volatile uint8_t slide = 0;     //Variabel til LCD update
volatile uint8_t gameflag = 0;  //Flag til spil update
volatile uint8_t updateGame = 0;//Variabel til spil update

void initTimer100Hz(){
    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
    TIM2->CR1 = 0x0000; // Configure timer 2 - disabled
    TIM2->ARR = 0x00009C3F; // Set reload value to 39999
    TIM2->PSC = 0x000F; // Set prescale value to 15
    TIM2->CR1 = 0x0001; // Configure timer 2 - enabled
    TIM2->DIER |= 0x0001; // Enable timer 2 interrupts
    slide = 0; //FlagEnable
    NVIC_SetPriority(TIM2_IRQn, 0000); // Set interrupt priority
    NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
}


void TIM2_IRQHandler(void){
    tid.centiseconds++;
    slide++;
    updateGame++;
    if (updateGame >= 6){//Spillet updateres med 25Hz
        gameflag = 1;
        updateGame = 0;
    }
//    if (slide >= 5) {//Bestemmer opdateringshastigheden af LCD
//        flag = 1;
//        slide = 0;
//    }
//    if (tid.centiseconds >= 100) {
//        tid.seconds++;
//        tid.centiseconds = 0;
//    }
//    if (tid.seconds >= 60) {
//        tid.minutes++;
//        tid.seconds=0;
//    }
//    if (tid.minutes == 60) {
//        tid.hours++;
//        tid.minutes=0;
//    }

    TIM2->SR &= ~0x0001; //Clear interrupt bit
}


void printTid(){
    uint8_t s,m,h;

        NVIC_DisableIRQ(TIM2_IRQn);
        s = tid.seconds;
        m = tid.minutes;
        h = tid.hours;
        NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
        printf("%d:%02d:%02d", h, m, s);


}

void printSplit (uint8_t c, uint8_t s, uint8_t m, uint8_t h){
    printf("%d:%02d:%02d.%02d", h, m, s, c);
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

uint8_t get_flag() {
    if (flag) {
        flag = 0;
        return 1;
    }
    return 0;
}

uint8_t get_game_flag() {
    if (gameflag) {
        gameflag = 0;
        return 1;
    }
    return 0;
}
