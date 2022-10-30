/*
 * Alarm.c
 *
 *  Created on: Oct 24, 2022
 *      Author: Idan Maoz
 */

#include "Alarm.h"
#include "Rtc.h"
#include "Buzzer.h"
#include "MyMain.h"
#include "Flash.h"
#include "Led.h"
#include <string.h>
#include <stdio.h>
#include "cmsis_os.h"
#define maxAlarms 10



Alarm alarms[maxAlarms];
uint32_t alarmsLen = 0;

void Alarm_add(char * name,DateTime dateTime)
{
	Alarm alarm;
	strncpy(alarm.name,name,maxNameSize);
	alarm.dateTime = dateTime;
	alarms[alarmsLen] = alarm;
	alarmsLen++;

	uint64_t* byteAlarms = (uint64_t*)(alarms);
	HAL_FLASH_Unlock();
	Flash_erase();
	Flash_program(byteAlarms, sizeof(alarms));
	HAL_FLASH_Lock();
	/*printf("%02d:%02d:%02d-%d-%02d/%02d/%02d\r\n",
					alarm.dateTime.hours, alarm.dateTime.min, alarm.dateTime.sec,
					alarm.dateTime.weekDay,
					alarm.dateTime.day, alarm.dateTime.month, alarm.dateTime.year);*/

}
void Alarm_delete(char * name)
{
	for(int i=0;i<alarmsLen;i++){
		if(!strcmp(name,alarms[i].name)){
			alarms[i]=alarms[alarmsLen-1];
			alarms[alarmsLen-1].isActive = 0;
			alarmsLen--;

			uint64_t* byteAlarms = (uint64_t*)(alarms);
			HAL_FLASH_Unlock();
			Flash_erase();
			Flash_program(byteAlarms, sizeof(alarms));
			HAL_FLASH_Lock();
		}
	}

}
void Alarm_stop(char * name)//ask what they mean
{


}

void Alarm_clearAll()
{
	for(int i=0;i<alarmsLen;i++){
		alarms[i].isActive = 0;
	}
	alarmsLen = 0;
	uint64_t* byteAlarms = (uint64_t*)(alarms);
	HAL_FLASH_Unlock();
	Flash_erase();
	Flash_program(byteAlarms, sizeof(alarms));
	HAL_FLASH_Lock();
}

void Alarm_edit(char * name,DateTime dateTime)
{
	for(int i=0;i<alarmsLen;i++){
		if(!strcmp(name,alarms[i].name)){
			alarms[i].dateTime=dateTime;
		}
	}
}

void Alarm_startTask(void* argument)
{
	Rtc* rtc = (Rtc*)argument;
	for(;;){
		if(alarmsLen!=0){
			for(int i=0;i<alarmsLen;i++){
				if(Rtc_convertToSec(&alarms[i].dateTime) == Rtc_getSeconds(rtc)){
					Buzzer_changeToOn(&bz1);//ask if it is good
					Led_changeToBlink(&ledR);
					Led_changeToBlink(&ledB);
					printf("Alarm %s turned on\r\n",alarms[i].name);
				}
				if(Buzzer_getState(&bz1) == BUZZER_STATE_OFF){
					Led_changeToOff(&ledB);
					Led_changeToOff(&ledR);
				}

			}
		}
		osDelay(1000);
	}

}
void Alarm_print(){
	printf("The existing alarms are:\r\n");
	for(int i=0;i<alarmsLen;i++){
		printf("%s %02d:%02d:%02d-%d-%02d/%02d/%02d\r\n",alarms[i].name,
					alarms[i].dateTime.hours, alarms[i].dateTime.min, alarms[i].dateTime.sec,
					alarms[i].dateTime.weekDay,alarms[i].dateTime.day, alarms[i].dateTime.month,
					alarms[i].dateTime.year);
	}
}

void Alarm_flashToAlarms()
{
	for (int i = 0 ; i<sizeof(alarms)/sizeof(Alarm); i++)
	{
		Alarm* alarm = (Alarm*)(0x08080000+(i*sizeof(Alarm)));
		if(alarm->isActive != 0){  //ask about this
			alarmsLen++;
		}
		alarms[i] = *alarm;
	}
}





