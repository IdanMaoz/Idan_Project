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
#include "Button.h"
#include <string.h>
#include <stdio.h>
#include "cmsis_os.h"
#define maxAlarms 10



Alarm alarms[maxAlarms];
uint32_t alarmsLen = 0;

/**
 * @brief  Alarm_add
 *         add alarm
 *         @note
 *
 *
 * @param char* name - the name of the alarm
 * @param DateTime dateTime - the time of the alarm
 * @retval 0 if the alarm doesn't exists, 1 if he exists.
 */
int Alarm_add(char * name,DateTime dateTime)
{
	for(int i=0;i<alarmsLen;i++){
		if(!strcmp(name,alarms[i].name)){
			return 0;
		}
	}
	Alarm alarm;
	strncpy(alarm.name,name,maxNameSize);
	alarm.countSnooze = 0;
	strncpy(alarm.melodyName,"melody0",maxNameSize);
	alarm.dateTime = dateTime;

	alarms[alarmsLen] = alarm;
	alarmsLen++;

	uint64_t* byteAlarms = (uint64_t*)(alarms);
	HAL_FLASH_Unlock();
	Flash_erase();
	Flash_program(byteAlarms, sizeof(alarms));
	HAL_FLASH_Lock();
	return 1;
}

/**
 * @brief  Alarm_delete
 *         delete alarm
 *         @note
 *
 *
 * @param char* name - the name of the alarm
 * @retval 0 if the alarm doesn't exists, 1 if he exists and deleted.
 */
int Alarm_delete(char * name)
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
			return 1;
		}
	}
	return 0;

}

/**
 * @brief  Alarm_stop
 *         stop alarm
 *         @note
 *
 *
 * @param char* name - the name of the alarm
 * @retval none
 */
void Alarm_stop(char * name)//ask what they mean
{

	Buzzer_changeToOff(&bz1);

}

/**
 * @brief  Alarm_changeMelody
 *         change the alarm melody
 *         @note
 *
 *
 * @param char* name - the name of the alarm
 * @param char* melody - the melody of the alarm
 * @retval 0 if the alarm doesn't exists, 1 if he exists and the melody changed.
 */
int Alarm_changeMelody(char * name,char* melody)
{
	for(int i=0;i<alarmsLen;i++){
		if(!strcmp(name,alarms[i].name)){
			strcpy(alarms[i].melodyName,melody);
			uint64_t* byteAlarms = (uint64_t*)(alarms);
			HAL_FLASH_Unlock();
			Flash_erase();
			Flash_program(byteAlarms, sizeof(alarms));
			HAL_FLASH_Lock();
			return 1;
		}
	}
	return 0;
}

/**
 * @brief  Alarm_clearAll
 *         deleted all alarms(change them to not active - isActive = 0)
 *         @note
 *
 *
 * @param none
 * @retval none
 */
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

/**
 * @brief  Alarm_edit
 *         edit the alarm time
 *         @note
 *
 *
 * @param char* name - the name of the alarm
 * @param DateTime dateTime - the time of the alarm
 * @retval none
 */
void Alarm_edit(char * name,DateTime dateTime)
{
	for(int i=0;i<alarmsLen;i++){
		if(!strcmp(name,alarms[i].name)){
			alarms[i].dateTime=dateTime;
		}
	}
}

/**
 * @brief  addSnoozeTime
 *         change alarm snooze
 *         @note
 *
 *
 * @param char* name - the name of the alarm
 * @param uint32_t count - the snooze count of alarm
 * @retval none
 */
void addSnoozeTime(char * name,uint32_t count)
{
	for(int i=0;i<alarmsLen;i++){
			if(!strcmp(name,alarms[i].name)){
				alarms[i].countSnooze = count;
			}
		}
}

/**
 * @brief  Alarm_startTask
 *         check if the time is equal to alarm time and handle the alarm
 *         @note
 *
 *
 * @param void* argument - a potential argument
 * @retval none
 */
void Alarm_startTask(void* argument)
{
	Rtc* rtc = (Rtc*)argument;
	for(;;){
		if(alarmsLen!=0){
			for(int i=0;i<alarmsLen;i++){
				if(Rtc_convertToSec(&alarms[i].dateTime) + 10*alarms[i].countSnooze  == Rtc_getSeconds(rtc)){
					Buzzer_changeToOn(&bz1);
					Buzzer_changeMelody(&bz1, alarms[i].melodyName);
					Led_changeToBlink(&ledR);
					Led_changeToBlink(&ledB);
					printf("Alarm %s turned on\r\n",alarms[i].name);
				}
				if(Buzzer_getState(&bz1) == BUZZER_STATE_OFF){
					Led_changeToOff(&ledB);
					Led_changeToOff(&ledR);
				}
				if(Button_getState(&btn2) == BUTTON_STATE_PRESS && Buzzer_getState(&bz1) == BUZZER_STATE_ON){
					Buzzer_changeToOff(&bz1);

				}
				if(Button_getState(&btn1) == BUTTON_STATE_PRESS && Buzzer_getState(&bz1) == BUZZER_STATE_ON){
					addSnoozeTime(alarms[i].name, alarms[i].countSnooze+1);

				}
			}
		}
		osDelay(1000);
	}
}

/**
 * @brief  Alarm_print
 *         print all the alarms
 *         @note
 *
 *
 * @param none
 * @retval none
 */
void Alarm_print(){
	printf("The existing alarms are:\r\n");
	for(int i=0;i<alarmsLen;i++){
		printf("%s %02d:%02d:%02d-%d-%02d/%02d/%02d %s\r\n",alarms[i].name,
					alarms[i].dateTime.hours, alarms[i].dateTime.min, alarms[i].dateTime.sec,
					alarms[i].dateTime.weekDay,alarms[i].dateTime.day, alarms[i].dateTime.month,
					alarms[i].dateTime.year,alarms[i].melodyName);
	}
}

/**
 * @brief  Alarm_flashToAlarms
 *         save all alarms in flash
 *         @note
 *
 *
 * @param none
 * @retval none
 */
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





