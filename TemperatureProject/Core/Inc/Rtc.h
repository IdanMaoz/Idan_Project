/*
 * Rtc.h
 *
 *  Created on: Nov 23, 2022
 *      Author: Idan Maoz
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_
#include "main.h"

typedef struct DateTime_
{
	int sec;
	int min;
	int hours;
	int weekDay;
	int day;
	int month;
	int year;
} DateTime;

class Rtc {
private:
	I2C_HandleTypeDef* _hi2c;
	uint8_t _devAddr;
public:
	Rtc(I2C_HandleTypeDef* _hi2c,uint8_t _devAddr);
	void getTime(DateTime * dateTime);
	void setTime(DateTime * dateTime);
	void timeStrTok(const char * params,DateTime* dateTime);


};

#endif /* INC_RTC_H_ */
