#ifndef RTC_H_INCLUDED
#define RTC_H_INCLUDED
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "struct.h"
#include "ansi.h"

void backupDomainAccess();
void initRTC24(RTC_InitTypeDef* RTC_InitStruct);
void initTime(uint8_t AMPM, uint8_t hours, uint8_t minutes, uint8_t seconds, RTC_TimeTypeDef* RTC_TimeStruct);
void initDate(uint8_t weekday, uint8_t date, uint8_t month, uint8_t year, RTC_DateTypeDef* RTC_DateStruct);

/** Remember before reading **/
//RTC_WaitForSynchro(); // Used before reading after initialization, update or wakeup from low power mode

#endif /* RTC_H_INCLUDED */
