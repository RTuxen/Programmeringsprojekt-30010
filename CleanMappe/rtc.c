#include "rtc.h"

void backupDomainAccess(){
    RCC->APB1ENR |= 0x10000000; //Enables the Power Controller (PWR) APB1 interface clock - RCC_APB1Periph_PWR

    // Enables access to Backup Domain
    PWR_BackupAccessCmd(ENABLE);

    // Resets the backup Domain
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

    // Turns on the LSE
    RCC_LSEConfig(RCC_LSE_ON);

    // Waits until the LSE is ready
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {}

    // Selects the RTC clock source
    RCC->BDCR |= 0x00000100; // RCC_RTCCLKSource_LSE

    // Enables the RTC
    RCC_RTCCLKCmd(ENABLE);

    // Deinitialize the RTC registers to their default reset values
    // Doesn't reset the clock source and the backup data
    RTC_DeInit();
}

void initRTC24(RTC_InitTypeDef* RTC_InitStruct){

    // Sets the values of the struct
    RTC_InitStruct->RTC_HourFormat = RTC_HourFormat_24; // Initialize the RTC_HourFormat
    RTC_InitStruct->RTC_AsynchPrediv = (uint32_t)0x7F;  // Initialize the RTC_AsynchPrediv to 127
    RTC_InitStruct->RTC_SynchPrediv = (uint32_t)0xFF;   // Initialize the RTC_SynchPrediv to 255


    // Disable the write protection for RTC registers
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    // Enter initialization mode
    RTC_EnterInitMode();

    // Clear RTC CR FMT Bit
    RTC->CR &= ((uint32_t)~(RTC_CR_FMT));

    // Set RTC_CR register
    RTC->CR |=  ((uint32_t)(RTC_InitStruct->RTC_HourFormat));

    // Configure the RTC PRER
    RTC->PRER = (uint32_t)(RTC_InitStruct->RTC_SynchPrediv);
    RTC->PRER |= (uint32_t)(RTC_InitStruct->RTC_AsynchPrediv << 16);

    // Exit Initialization mode
    RTC_ExitInitMode();

    // Enables write protection
    RTC->WPR = 0xFF;
}

void initTime(uint8_t AMPM, uint8_t hours, uint8_t minutes, uint8_t seconds, RTC_TimeTypeDef* RTC_TimeStruct){
    // Parameters should be in BCD format - for example: 1 = 0x01 og 12 = 0x12
    // AM = 0x00, PM = 0x40

    // Sets the values of the struct
    RTC_TimeStruct->RTC_H12 = AMPM;
    RTC_TimeStruct->RTC_Hours = hours;
    RTC_TimeStruct->RTC_Minutes = minutes;
    RTC_TimeStruct->RTC_Seconds = seconds;

    // Sets the time to the chosen values
    RTC_SetTime(RTC_Format_BCD, RTC_TimeStruct);
}

void initDate(uint8_t weekday, uint8_t date, uint8_t month, uint8_t year, RTC_DateTypeDef* RTC_DateStruct){
    // Parameters should be in BCD format - for example: 1 = 0x01 og 12 = 0x12

    // Sets the values of the struct
    RTC_DateStruct->RTC_WeekDay = weekday;
    RTC_DateStruct->RTC_Date = date;
    RTC_DateStruct->RTC_Month = month;
    RTC_DateStruct->RTC_Year = year;

    // Sets the date to the chosen values
    RTC_SetDate(RTC_Format_BCD, RTC_DateStruct);
}
