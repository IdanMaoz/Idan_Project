
#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"
#include <stdint.h>

typedef struct Rtc_
{
	I2C_HandleTypeDef * hi2c;
	uint8_t devAddr;
} Rtc;

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


void Rtc_init(Rtc * rtc, I2C_HandleTypeDef * hi2c, uint32_t devAddr);

void Rtc_getTime(Rtc * rtc, DateTime * dateTime);

uint32_t Rtc_getSeconds(Rtc * rtc);

uint32_t Rtc_convertToSec(DateTime * dateTime);
void Rtc_setTime(Rtc * rtc);
#endif /* INC_RTC_H_ */
