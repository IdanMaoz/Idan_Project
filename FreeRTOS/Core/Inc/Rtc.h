/*
 * Rtc.h
 *
 *  Created on: Sep 15, 2022
 *      Author: student
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_
#include "stdint.h"
typedef struct dateTime_{
	uint32_t seconds;
	uint32_t minutes;
	uint32_t hours;
	uint32_t day;
	uint32_t date;
	uint32_t month;
	uint32_t year;

}dateTime;
extern dateTime date_time;
#endif /* INC_RTC_H_ */
