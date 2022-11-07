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
	uint32_t isActive;
	char melodyName[maxNameSize];
} Alarm;


int Alarm_add(char * name,DateTime dateTime);
void Alarm_print();
int Alarm_delete(char * name);
void Alarm_clearAll();
void Alarm_stop(char * name);
void Alarm_edit(char * name,DateTime dateTime);
int Alarm_changeMelody(char * name,char* melody);
void Alarm_flashToAlarms();
#endif /* INC_ALARM_H_ */
