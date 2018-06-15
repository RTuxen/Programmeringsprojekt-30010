#include "rtc.h"

void initRTC(){
    RTC->ISR |= 0x00000001 << 7; //Enter initialization mode - Calender stopped and can be configured
    RTC->ISR |= 0x00000001 << 6; //Enter initialization phase mode - Allows calender updates

    RTC->TR |= 0x00123456; //Calender is configured to 24 hours format with the timer 12:34:56, see page 740 i reference manual for more info
    //0000 0000 0 01 0010 0 011 0100 0 101 0110
    RTC->DR |= 0x0050C613; //Calender is configured to year 18, weekday wednesday, month 06, date 13
    //0000 0000 0010 1000 011 0 00110 00 01 0011

    RTC->PRER &= 0x00017FFF; //Sets synchronous prescaler to 32767
}

##### Backup Domain Reset #####
RCC_BackupResetCmd(); // Sets all RTC registers and the RCC_BDCR register to their reset values

##### Backup Domain Access #####
RCC_APB1PeriphClockCmd(); // Enables the Power Controller (PWR) APB1 interface clock
PWR_BackupAccessCmd(); //Enables access to Backup domain
RCC_RTCCLKConfig(); // Selects the RTC clock source
RCC_RTCCLKCmd(); // Enables the RTC

##### How to use this driver #####
RTC_Init(); //Configure the RTC Prescaler and RTC hour format

/** Time and Date configuration **/
RTC_SetTime(); // Sets time
RTC_SetDate(); // Sets date

/** Read Time and Date **/
RTC_GetTime(); // Gets time
RTC_GetDate(); // Gets date

RTC_GetSubSecond(); // Reads subseconds
RTC_DayLightSavingConfig(); // Adds or subs one hour to the calender

##### Initialization and Configuration functions #####
The RTC_WaitForSynchro();

ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct);
