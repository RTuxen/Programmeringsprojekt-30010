#include "timer.h"

volatile uint8_t flag = 0;       //Flag til LCD update
volatile uint8_t slide = 0;      //Variabel til LCD update
volatile uint8_t gameflag = 0;   //Flag til spil update
volatile uint8_t updateGame = 0; //Variabel til spil update
volatile uint8_t gametime = 0;   // Variabel til

void initTimer1000Hz(){
    RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;
    TIM15->CR1 = 0x0000; // Configure timer 15 - disabled
    //TIM15->ARR = 0x9C3F; // Set reload value to 39999
    TIM15->ARR = 0x00000F9F; // Set reload value to 3999
    TIM15->PSC = 0x000F; // Set prescale value to 15
    TIM15->DIER |= 0x0001; // Enable timer 2 interrupts

    NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0001); // Set interrupt priority
    NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt

    TIM15->CR1 |= 0x0001; // Configure timer 15 - enabled
}

void TIM1_BRK_TIM15_IRQHandler(void){

    tid.randomAngle++;
    gametime++;
    tid.joystickdebouncer++;
    slide++;
    updateGame++;
    tid.soundtime++;
    if (updateGame >= 5){//Spillet updateres
        gameflag = 1;
        updateGame = 0;
    }
    if (slide >= 50) {//Bestemmer opdateringshastigheden af LCD
        flag = 1;
        slide = 0;
    }
    if (gametime >= 100) {
        tid.seconds++;
        gametime = 0;
    }
    if (tid.randomAngle >= 1000){
        tid.randomAngle = 0;
    }
    TIM15->SR &= ~0x0001; //Clear interrupt bit
}

void initTimerPWM(){
    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
    TIM2->CR1 = 0x0000; // Configure timer 2 - disabled
    TIM2->ARR = 0x000003E7; // Set reload value to 999
    TIM2->PSC = 0x000F; // Set prescale value to 15
    TIM2->CR1 = 0x0001; // Configure timer 2 - enabled
    TIM2->DIER |= 0x0001; // Enable timer 2 interrupts

    TIM2->CCER &= ~TIM_CCER_CC3P; // Clear CCER register
    TIM2->CCER |= 0x00000001 << 8; // Enable OC3 output
    TIM2->CCMR2 &= ~TIM_CCMR2_OC3M; // Clear CCMR2 register
    TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
    TIM2->CCMR2 |= TIM_OCMode_PWM1; // Set output mode to PWM1
    TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
    TIM2->CCMR2 |= TIM_OCPreload_Enable;
    TIM2->CCR3 = 500; // Set duty cycle to 50 %

    NVIC_SetPriority(TIM2_IRQn, 0001); // Set interrupt priority
    NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
}

void setFreq(uint16_t freq) {
 uint32_t reload = (64e6 / freq / 16) - 1;
 TIM2->ARR = reload; // Set auto reload value
 TIM2->CCR3 = reload/2; // Set compare register
 TIM2->EGR |= 0x01;
 }


void TIM2_IRQHandler(void){
    TIM2->SR &= ~0x0001; //Clear interrupt bit
}

void setTimer(uint8_t difficulty, uint8_t levelspeed){
    TIM15->CR1 = 0x0000; // Configure timer 2 - disabled
    TIM15->ARR = 0x00009C3F/(2*difficulty+levelspeed); // Set reload value depending on difficulty and speed
    TIM15->PSC = 0x000F; // Set prescale value to 15
    TIM15->CR1 = 0x0001; // Configure timer 2 - enabled
    TIM15->EGR |= 0x0001;
}

void setTimerDefault(){
    TIM15->CR1 = 0x0000; // Configure timer 2 - disabled
    TIM15->ARR = 0x00000F9F; // Set reload value to 3999
    TIM15->PSC = 0x000F; // Set prescale value to 15
    TIM15->CR1 = 0x0001; // Configure timer 2 - enabled
    TIM15->EGR |= 0x0001;
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

//void printTid(){
//    uint8_t s,m,h;
//
//        NVIC_DisableIRQ(TIM2_IRQn);
//        s = tid.seconds;
//        m = tid.minutes;
//        h = tid.hours;
//        NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
//        printf("%d:%02d:%02d", h, m, s);
//
//
//}

//void printSplit (uint16_t ms, uint8_t s, uint8_t m, uint8_t h){
//    printf("%d:%02d:%02d.%02d", h, m, s, ms);
//}


//void stopWatchControl(int8_t value){
//    if (value == 16){ // Center - Stop/Start (enable and disable of clock)
//        if (TIM2->CR1 & 0x0001){
//            TIM2->CR1 = 0x0000;
//        } else{
//            TIM2->CR1 = 0x0001;
//        }
//    } else if (value == 4){ // Left - prints split 1
//        NVIC_DisableIRQ(TIM2_IRQn);
//        uint16_t ms = tid.centiseconds;
//        int8_t s = tid.seconds;
//        int8_t m = tid.minutes;
//        int8_t h = tid.hours;
//        NVIC_EnableIRQ(TIM2_IRQn);
//        printSplit(ms,s,m,h);
//    } else if (value == 8){ // Right - Prints split 2
//        NVIC_DisableIRQ(TIM2_IRQn);
//        uint16_t ms = tid.centiseconds;
//        int8_t s = tid.seconds;
//        int8_t m = tid.minutes;
//        int8_t h = tid.hours;
//        NVIC_EnableIRQ(TIM2_IRQn);
//        printSplit(ms,s,m,h);
//    } else if (value == 2){ // Down - Resets timer
//        TIM2->CR1 = 0x0000;
//        tid.centiseconds = 0;
//        tid.seconds = 0;
//        tid.minutes = 0;
//        tid.hours = 0;
//    }
//}
