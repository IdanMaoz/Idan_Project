/*
 * Rtc.cpp
 *
 *  Created on: Nov 23, 2022
 *      Author: Idan Maoz
 */

#include "Rtc.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#define RTC_START_STOP      (1 << 7)
#define RTC_DATE_TIME_SIZE  7

/**
 * @brief  Rtc
 *         init the rtc
 *         @note
 *
 *
 * @param  I2C_HandleTypeDef* hi2c - the hi2c of rtc
 * @param  uint8_t devAddr - the address of rtc
 * @retval none
 */
Rtc::Rtc(I2C_HandleTypeDef* hi2c,uint8_t devAddr) {
	_hi2c = hi2c;
	_devAddr = devAddr;

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
int Rtc::bcdToInt(uint8_t bcd)
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

uint8_t Rtc::intToBcd(int value, int minVal, int maxVal)
{
	if (value < minVal || value > maxVal) {
		return 0;
	}

	return ((value / 10) << 4) | (value % 10);
}

/**
 * @brief  getTime
 *         get the time from rtc
 *         @note
 *
 *
 * @param  DateTime* dateTime - to insert the time
 * @retval none
 */
void Rtc::getTime(DateTime * dateTime)
{
	uint8_t buffer[RTC_DATE_TIME_SIZE];
	HAL_I2C_Mem_Read(_hi2c, _devAddr, 0, 1, buffer, RTC_DATE_TIME_SIZE, 0xFF);


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
 * @brief  setTime
 *         set the rtc time
 *         @note
 *
 *
 * @param  DateTime* dateTime - to set the time
 * @retval none
 */
void Rtc::setTime(DateTime * dateTime)
{
	uint8_t buffer[RTC_DATE_TIME_SIZE];

	buffer[0] = intToBcd(dateTime->sec, 0, 59);
	buffer[1] = intToBcd(dateTime->min, 0, 59);
	buffer[2] = intToBcd(dateTime->hours, 0, 59);
	buffer[3] = dateTime->weekDay < 1 || dateTime->weekDay > 7 ? 0 : dateTime->weekDay;
	buffer[4] = intToBcd(dateTime->day, 1, 31);
	buffer[5] = intToBcd(dateTime->month, 1, 12);
	buffer[6] = intToBcd(dateTime->year, 1, 99);
	HAL_I2C_Mem_Write(_hi2c, _devAddr, 0, 1, buffer, RTC_DATE_TIME_SIZE, 0xFF);
	printf("Time set successfully\r\n");
}

/**
 * @brief  checkToken
 *         to check if the number is in range
 *         @note
 *
 *
 * @param  char* token - string number
 * @param int low - the minimum that number can be
 * @param int high - the maximum that number can be
 * @retval 0 if number isn't in range, 1 if it is
 */
int Rtc::checkToken(char* token,int low,int high)
{
	int tokInt = atoi(token);
	if(tokInt < low || tokInt > high){
		printf("You need to write correct date\r\n");
		return 0;
	}
	return 1;
}

/**
 * @brief  timeStrTok
 *         split the time char
 *         @note
 *
 *
 * @param  const char* params - string of the time
 * @param DateTime* dateTime - time to insert inside
 * @retval none
 */
void Rtc::timeStrTok(const char * params,DateTime* dateTime)
{
	char* token;
	char cpyParm[20];
	memcpy(cpyParm,params,strlen(params)+1);
	token = strtok(cpyParm, ":");
	if(!checkToken(token,0,59)){
		return;
	}
	dateTime->hours = atoi(token);
	token = strtok(NULL, ":");
	if(!checkToken(token,0,59)){
		return ;
	}
	dateTime->min = atoi(token);
	token = strtok(NULL, "-");
	if(!checkToken(token,0,59)){
		return;
	}
	dateTime->sec = atoi(token);
	token = strtok(NULL, "-");
	if(!checkToken(token,0,7)){
		return;
	}
	dateTime->weekDay = atoi(token);
	token = strtok(NULL, "/");
	if(!checkToken(token,1,31)){
		return;
	}
	dateTime->day = atoi(token);
	token = strtok(NULL, "/");
	if(!checkToken(token,1,12)){
		return;
	}
	dateTime->month = atoi(token);
	token = strtok(NULL, "/");
	if(!checkToken(token,1,99)){
		return;
	}
	dateTime->year = atoi(token);
	token = strtok(NULL, "/");
	if(token!=NULL){
		return;
	}
	setTime(dateTime);
}
