/*
 * Rtc.h
 *
 *  Created on: Nov 23, 2022
 *      Author: Idan Maoz
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

struct DateTime
{
	int sec;
	int min;
	int hours;
	int weekDay;
	int day;
	int month;
	int year;
};

class Rtc {
private:
	I2C_HandleTypeDef* _hi2c;
	uint8_t _devAddr;
public:
	Rtc(I2C_HandleTypeDef* _hi2c,uint8_t _devAddr);
	void getTime(DateTime * dateTime);
	void setTime(DateTime * dateTime);
	void timeStrTok(const char * params,DateTime* dateTime);
private:
	int bcdToInt(uint8_t bcd);
	uint8_t intToBcd(int value, int minVal, int maxVal);
	int checkToken(char* token,int low,int high);
};

#endif /* INC_RTC_H_ */
