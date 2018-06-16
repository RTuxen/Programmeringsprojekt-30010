#ifndef RTC_H_INCLUDED
#define RTC_H_INCLUDED
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "struct.h"

/** Functions used for the initializationfunctions **/
/*
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct); // Initializes the RTC_InitStruct
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct); // Initializes the RTC format and prescaler

void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct); //Initializes the RTC_TimeStruct
ErrorStatus RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct); // Initializes the time

void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct); //Initializes the RTC_DateStruct
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct); // Initializes the date
*/

/** Selfmade functions **/

void backupDomainAccess();
void initRTC24(RTC_InitTypeDef* RTC_InitStruct);
void initTime(uint8_t AMPM, uint8_t hours, uint8_t minutes, uint8_t seconds, RTC_TimeTypeDef* RTC_TimeStruct);
void initDate(uint8_t weekday, uint8_t date, uint8_t month, uint8_t year, RTC_DateTypeDef* RTC_DateStruct);

#endif /* RTC_H_INCLUDED */













//Structs Used
///** Initstruct **/
//typedef struct
//{
//  uint32_t RTC_HourFormat;   /*!< Specifies the RTC Hour Format.
//                             This parameter can be a value of @ref RTC_Hour_Formats */
//
//  uint32_t RTC_AsynchPrediv; /*!< Specifies the RTC Asynchronous Predivider value.
//                             This parameter must be set to a value lower than 0x7F */
//
//  uint32_t RTC_SynchPrediv;  /*!< Specifies the RTC Synchronous Predivider value.
//                             This parameter must be set to a value lower than 0x1FFF */
//}RTC_InitTypeDef;
//
//
///** Timestruct **/
//typedef struct
//{
//  uint8_t RTC_Hours;    /*!< Specifies the RTC Time Hour.
//                        This parameter must be set to a value in the 0-12 range
//                        if the RTC_HourFormat_12 is selected or 0-23 range if
//                        the RTC_HourFormat_24 is selected. */
//
//  uint8_t RTC_Minutes;  /*!< Specifies the RTC Time Minutes.
//                        This parameter must be set to a value in the 0-59 range. */
//
//  uint8_t RTC_Seconds;  /*!< Specifies the RTC Time Seconds.
//                        This parameter must be set to a value in the 0-59 range. */
//
//  uint8_t RTC_H12;      /*!< Specifies the RTC AM/PM Time.
//                        This parameter can be a value of @ref RTC_AM_PM_Definitions */
//}RTC_TimeTypeDef;
//
///** Calenderstruct **/
//typedef struct
//{
//  uint8_t RTC_WeekDay; /*!< Specifies the RTC Date WeekDay.
//                        This parameter can be a value of @ref RTC_WeekDay_Definitions */
//
//  uint8_t RTC_Month;   /*!< Specifies the RTC Date Month (in BCD format).
//                        This parameter can be a value of @ref RTC_Month_Date_Definitions */
//
//  uint8_t RTC_Date;     /*!< Specifies the RTC Date.
//                        This parameter must be set to a value in the 1-31 range. */
//
//  uint8_t RTC_Year;     /*!< Specifies the RTC Date Year.
//                        This parameter must be set to a value in the 0-99 range. */
//}RTC_DateTypeDef;
