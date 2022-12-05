/*
 * Rtc.c
 *
 *  Created on: 24 באוק׳ 2022
 *      Author: Idan Maoz
 */

#include "Rtc.h"
#include "main.h"

#include <stdint.h>

#define RTC_START_STOP      (1 << 7)
#define RTC_DATE_TIME_SIZE  7
#define DEVICE_ADDR         0xD0


const uint32_t DaysInYear    = 365;
const uint32_t SecondsInMin  = 60;
const uint32_t SecondsInHour = 3600;
const uint32_t SecondsInDay  = 86400;

static const int _daysUntilMonth[] = {
		0,
		31,
		59,
		90,
		120,
		151,
		181,
		212,
		243,
		273,
		304,
		334,
		365
};

/**
 * @brief  Rtc_init
 *         init the rtc
 *         @note
 *
 *
 * @param Rtc* rtc - the rtc
 * @param  I2C_HandleTypeDef* hi2c - the hi2c of rtc
 * @param  uint8_t devAddr - the address of rtc
 * @retval none
 */
void Rtc_init(Rtc * rtc, I2C_HandleTypeDef * hi2c, uint32_t devAddr)
{
	rtc->hi2c = hi2c;
	rtc->devAddr = devAddr;
}

/**
 * @brief  bcdToInt
 *         convert bcd to int
 *         @note
 *
 *
 * @param  uint8_t bcd - the number in bcd
 * @retval the number in int
 */
static int bcdToInt(uint8_t bcd)
{
	return (bcd >> 4) * 10 + (bcd & 0x0F);
}

/**
 * @brief  intToBcd
 *         convert int to bcd
 *         @note
 *
 *
 * @param  int value - the number in int
 * @param int minVal - the minimum that value can be
 * @param int maxVal - the maximum that value can be
 * @retval 0 if value isn't in range, the number in bcd if it is in range
 */
static uint8_t intToBcd(int value, int minVal, int maxVal)
{
	if (value < minVal || value > maxVal) {
		return 0;
	}
	return ((value / 10) << 4) | (value % 10);
}

/**
 * @brief  Rtc_getTime
 *         get the time from rtc
 *         @note
 *
 *
 *@param Rtc* rtc- the rtc
 * @param  DateTime* dateTime - to insert the time
 * @retval none
 */
void Rtc_getTime(Rtc * rtc, DateTime * dateTime)
{
	uint8_t buffer[RTC_DATE_TIME_SIZE];
	HAL_I2C_Mem_Read(rtc->hi2c, rtc->devAddr, 0, 1, buffer, RTC_DATE_TIME_SIZE, 0xFF);

	// remove stop bit if set
	buffer[0] &= ~RTC_START_STOP;
	dateTime->sec = bcdToInt(buffer[0]);
	dateTime->min = bcdToInt(buffer[1]);
	dateTime->hours = bcdToInt(buffer[2]);
	dateTime->weekDay = buffer[3] & 0x07;
	dateTime->day = bcdToInt(buffer[4]);
	dateTime->month = bcdToInt(buffer[5]);
	dateTime->year = bcdToInt(buffer[6]);
	
}

/**
 * @brief  Rtc_getSeconds
 *         get the seconds from rtc
 *         @note
 *
 *
 * @param  Rtc* rtc - the rtc
 * @retval the rtc in seconds
 */
uint32_t Rtc_getSeconds(Rtc * rtc)
{
	// calculate seconds from 00:00:00 1/1/2020
	DateTime dateTime;
	Rtc_getTime(rtc, &dateTime);

	uint32_t seconds = dateTime.sec +
			dateTime.min * SecondsInMin +
			dateTime.hours * SecondsInHour +
			dateTime.day * SecondsInDay +
			_daysUntilMonth[dateTime.month - 1] * SecondsInDay +
			dateTime.year * DaysInYear * SecondsInDay;
	if (dateTime.year % 4 == 0 && dateTime.month > 2) {
		// if current year is a leap year and month is after February
		// add seconds for February 29
		seconds += SecondsInDay;
	}
	// add seconds for all previous leap years
	seconds += (dateTime.year / 4) * SecondsInDay;
	return seconds;
}

/**
 * @brief  Rtc_convertToSec
 *         convert time to be in seconds
 *         @note
 *
 *
 * @param  DateTime * dateTime - the time
 * @retval the time in seconds
 */
uint32_t Rtc_convertToSec(DateTime * dateTime)
{
	// calculate seconds from 00:00:00 1/1/2020
	uint32_t seconds = dateTime->sec +
			dateTime->min * SecondsInMin +
			dateTime->hours * SecondsInHour +
			dateTime->day * SecondsInDay +
			_daysUntilMonth[dateTime->month - 1] * SecondsInDay +
			dateTime->year * DaysInYear * SecondsInDay;
	if (dateTime->year % 4 == 0 && dateTime->month > 2) {
		// if current year is a leap year and month is after February
		// add seconds for February 29
		seconds += SecondsInDay;
	}
	// add seconds for all previous leap years
	seconds += (dateTime->year / 4) * SecondsInDay;
	return seconds;
}

/**
 * @brief  Rtc_setTime
 *         set the rtc time
 *         @note
 *
 *
 * @param  DateTime* dateTime - to set the time
 * @retval none
 */
void Rtc_setTime(Rtc * rtc)
{
	uint8_t buffer[RTC_DATE_TIME_SIZE];

	buffer[0] = intToBcd(0, 0, 59);
	buffer[1] = intToBcd(0, 0, 59);
	buffer[2] = intToBcd(0, 0, 24);
	buffer[3] = 0 < 1 || 0 > 7 ? 0 : 1;
	buffer[4] = intToBcd(1, 1, 31);
	buffer[5] = intToBcd(1, 1, 12);
	buffer[6] = intToBcd(1, 1, 99);
	HAL_I2C_Mem_Write(rtc->hi2c, rtc->devAddr, 0, 1, buffer, RTC_DATE_TIME_SIZE, 0xFF);
}



