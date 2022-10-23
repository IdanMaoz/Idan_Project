/*
 * printRtcAndSensor.c
 *
 *  Created on: Sep 15, 2022
 *      Author: student
 */

#include <printData.h>
#include "Rtc.h"
#include "Adc.h"
#include "stdio.h"
#include "cmsis_os.h"
void printData_task(void * argumnt)
{
	for(;;){
		printf("The date time is: %lu:%lu:%lu:%lu:%lu:%lu:%lu\r\n",date_time.year,date_time.month,date_time.date,date_time.day,
				date_time.hours, date_time.minutes,date_time.seconds);
		printf("The light sensor value is: %lu\r\n",ltsensor);
		osDelay(1000);
	}
}
