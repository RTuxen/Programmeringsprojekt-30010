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

//##### Backup Domain Reset #####
//RCC_BackupResetCmd(); // Sets all RTC registers and the RCC_BDCR register to their reset values
//
//##### Backup Domain Access #####
//RCC_APB1PeriphClockCmd(); // Enables the Power Controller (PWR) APB1 interface clock
//void PWR_BackupAccessCmd(FunctionalState NewState); //Enables access to Backup domain
//void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource); // Selects the RTC clock source
//void RCC_RTCCLKCmd(FunctionalState NewState); // Enables the RTC - Must only be used after RTC clock source is selected
//
//##### How to use this driver #####
//RTC_Init(); //Configure the RTC Prescaler and RTC hour format
//
///** Time and Date configuration **/
//RTC_SetTime(); // Sets time
//RTC_SetDate(); // Sets date
//
///** Read Time and Date **/
//RTC_GetTime(); // Gets time
//RTC_GetDate(); // Gets date
//
//RTC_GetSubSecond(); // Reads subseconds
//RTC_DayLightSavingConfig(); // Adds or subs one hour to the calender
//
//##### Initialization and Configuration functions #####
//RTC_WaitForSynchro(); // Used before reading after initialization, update or wakeup from low power mode

void backupDomainAccess(){
    RCC->APB1ENR |= RCC_APB1Periph_PWR; //Enables the Power Controller (PWR) APB1 interface clock
    PWR_BackupAccessCmd(ENABLE); // Enables access to Backup Domain
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); // Selects the RTC clock source
    RCC_RTCCLKCmd(ENABLE); // Enables the RTC
}

void initRTC24(RTC_InitTypeDef* RTC_InitStruct){
    RTC_StructInit(RTC_InitStruct);// Initializes to 24 hour format, AsPre = 127 and SPre = 255
    RTC_Init(RTC_InitStruct);//First disables write protection
    //then when finished, it exits initialization mode and enables write protection
}

void initTime(uint8_t AMPM, uint8_t hours, uint8_t minutes, uint8_t seconds, RTC_TimeTypeDef* RTC_TimeStruct){
    // AM = 0x00, PM = 0x40
    // Parametre skal være i BCD format - f.eks. 1 = 0x01 og 12 = 0x12
    RTC_TimeStruct->RTC_H12 = AMPM;
    RTC_TimeStruct->RTC_Hours = hours;
    RTC_TimeStruct->RTC_Minutes = minutes;
    RTC_TimeStruct->RTC_Seconds = seconds;

    RTC_SetTime(RTC_Format_BCD, RTC_TimeStruct);
}

void initDate(uint8_t weekday, uint8_t date, uint8_t month, uint8_t year, RTC_DateTypeDef* RTC_DateStruct){
    // Parametre skal være i BCD format - f.eks. 1 = 0x01 og 12 = 0x12
    RTC_DateStruct->RTC_WeekDay = weekday;
    RTC_DateStruct->RTC_Date = date;
    RTC_DateStruct->RTC_Month = month;
    RTC_DateStruct->RTC_Year = year;

    RTC_SetDate(RTC_Format_BCD, RTC_DateStruct);
}





////Sets the RTC to 24 hour format and the asynchronous prescaler to 127 and synchronous prescaler to 255
//struct RTC_InitTypeDef RTC_InitStruct;
//RTC_StructInit(&RTC_InitStruct);// Initializes to 24 hour format, AsPre = 127 and SPre = 255
//RTC_Init(&RTC_InitStruct);//First disables write protection, then when finished, it exits initialization mode and enables write protection
//
//// Sets Time to 00h:00min:00sec
//struct RTC_TimeTypeDef RTC_TimeStruct;
//RTC_TimeStructInit(&RTC_TimeStruct);// Initializes Time to 00h:00min:00sec
//RTC_SetTime(&RTC_TimeStruct);
//
//// Sets date to Monday, January 01 xx00
//struct RTC_DateTypeDef RTC_DateStruct;
//RTC_DateStructInit(&RTC_DateStruct);// Initializes date to Monday, January 01 xx00
//RTC_SetDate(&RTC_DateStruct);

