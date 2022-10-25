/*
 * Alarm.h
 *
 *  Created on: Oct 24, 2022
 *      Author: Idan Maoz
 */

#ifndef INC_ALARM_H_
#define INC_ALARM_H_

#define maxNameSize 20
#include "Rtc.h"
typedef struct Alarm_
{
	char name[maxNameSize];
	DateTime dateTime;
} Alarm;


void Alarm_add(char * name,DateTime dateTime);
void Alarm_print();
void Alarm_delete(char * name);
void Alarm_clearAll();
void Alarm_edit(char * name,DateTime dateTime);
#endif /* INC_ALARM_H_ */
