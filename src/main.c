#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

//#include "menu.h"

#include "game.h"


int main(void)
    {

    // Initialize terminal connection
    init_usb_uart( 230400 ); // Initialize USB serial at 9600 baud

    /***************************/
	/* Create struct           */
	/***************************/

	struct game_state_t gs;//Danner et game state struct


    /***************************/
	/* Initialization          */
	/***************************/

    initTimer1000Hz(); //Initializes 1MHz clock TIM2
    initJoystick(); //Initializes joystick
    init_spi_lcd(); //Initializes LCD
    initADC(); // Initializes ADC
    initTimerPWM(); // Initializes PWM
    initBuzzer(); // Initializes piezo buzzer
    I2C_init(); // Initializes the onboard I2C
    initGameState(&gs); //Initializes game_state_t
    backupDomainAccess(); // Gives backup domain access
    initRTC24(&gs.RTC_InitStruct); // Initializes the hour format to 24, AsyncPrescaler to 127 and SyncPrescaler to 255
    initTime(0x00, 0x10, 0x58, 0x45, &gs.RTC_TimeStruct); // Initializes the time to 10:58:45
    initDate(0x02, 0x19, 0x06, 0x18, &gs.RTC_DateStruct); // Initializes the date to Tuesday, 19/06 year 18


	/***************************/
	/* Start game	           */
	/***************************/

    clrscr(); // Clears screen
    hideCursor(); // Hides cursor
    chooseMenuOptions(&gs); // Enters main menu




        while(1){
        }
}






