/*
 * Rtc.c
 *
 *  Created on: Sep 15, 2022
 *      Author: student
 */

#include "Rtc.h"
#include "main.h"
#include "cmsis_os.h"

extern I2C_HandleTypeDef hi2c1;
dateTime date_time;
uint8_t ptr[10];
void Rtc_readDateTask(void *argument)
{

	for(;;){
		HAL_I2C_Mem_Read(&hi2c1,  0xD0, 0, 1, ptr, 7, 0xff);
		uint8_t sec1 = ptr[0] & 15;
		uint8_t sec2= ptr[0]>>4;
		date_time.seconds=sec2*10+sec1;

		uint8_t min1= ptr[1] & 15;
		uint8_t min2= ptr[1]>>4;
		date_time.minutes=min2*10+min1;

		uint8_t hr1=ptr[2] & 15;
		uint8_t hr2=ptr[2]>>4;
		date_time.hours=hr2*10+hr1;

		date_time.day=ptr[3];


		uint8_t date1=ptr[4] & 15;
		uint8_t date2=ptr[4]>>4;
		date_time.date=date2*10+date1;

		uint8_t month1=ptr[5] & 15;
		uint8_t month2=ptr[5]>>4;
		date_time.month=month2*10+month1;

		uint8_t year1=ptr[6] & 15;
		uint8_t year2=ptr[6]>>4;
		date_time.year=year2*10+year1;

		osDelay(1000);

	}
}
