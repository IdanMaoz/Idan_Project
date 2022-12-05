/*
 * CLI.c
 *
 *  Created on: 12 Jul 2022
 *      Author: student
 */

#include <MyMain.h>
#include "Cli.h"
#include "Communication.h"
#include "Rtc.h"
#include "Alarm.h"

#include <stdlib.h>
#include <string.h>
#include "stdio.h"

/**
 * @brief  checkToken
 *         check if token is between low and high
 *         @note
 *
 *
 * @param  char* token - a time
 * @param  int low - the lower time token can be
 * @param  int high - the higher time token can be
 * @retval 0 if token isn't between low and hight, 1 if it is
 */
static int checkToken(char* token,int low,int high)
{
	int tokInt = atoi(token);
	if(tokInt < low || tokInt > high){
		return 0;
	}
	return 1;
}

/**
 * @brief  timeStrTok
 *         handle the char time
 *         @note
 *
 *
 * @param  char* params - the time in char
 * @param  DateTime* dateTime - date time struct
 * @retval 0 if params isn't ok, 1 if it is ok
 */
static int timeStrTok(char * params,DateTime* dateTime)
{
	char* token;
	token = strtok(params, ":");
	if(!checkToken(token,0,59)){
		return 0;
	}
	dateTime->hours = atoi(token);
	token = strtok(NULL, ":");
	if(!checkToken(token,0,59)){
		return 0;
	}
	dateTime->min = atoi(token);
	token = strtok(NULL, "-");
	if(!checkToken(token,0,59)){
		return 0;
	}
	dateTime->sec = atoi(token);
	token = strtok(NULL, "-");
	if(!checkToken(token,0,7)){
		return 0;
	}
	dateTime->weekDay = atoi(token);
	token = strtok(NULL, "/");
	if(!checkToken(token,1,31)){
		return 0;
	}
	dateTime->day = atoi(token);
	token = strtok(NULL, "/");
	if(!checkToken(token,1,12)){
		return 0;
	}
	dateTime->month = atoi(token);
	token = strtok(NULL, "/");
	if(!checkToken(token,1,99)){
		return 0;
	}
	dateTime->year = atoi(token);
	token = strtok(NULL, "/");
	if(token!=NULL){
		return 0;
	}
	return 1;
}

/**
 * @brief  paramStrTok
 *         handle the char
 *         @note
 *
 *
 * @param  char* params - the param in char
 * @retval 0 for change date, 1 for change melody, 2 for rep the melody
 */
static int paramStrTok(char * params)
{
	 char * token = strtok(params, "0123456789");
	 if(!strcmp(token,"melody")){
		 return 1;
	 }
	 else if(!strcmp(token,"rep")){
		 return 2;
	 }
	 else{
		 return 0;
	 }
}

/**
 * @brief  cmdGetSeconds
 *         cmd command to get rtc in seconds
 *         @note
 *
 *
 * @param  void* obj - the object(rtc)
 * @param  char* name - optional name
 *  @param  char* params - optional params
 * @retval none
 */
static void cmdGetSeconds(void* obj, char* name,char* params)
{
	Rtc* rtc = (Rtc*)obj;
	uint32_t sec = Rtc_getSeconds(rtc);
	printf("The sec is: %lu\r\n",sec);
}

/**
 * @brief  cmdListAlarms
 *         cmd command to print all alarms
 *         @note
 *
 *
 * @param  void* obj - optional object
 * @param  char* name - optional name
 *  @param  char* params - optional params
 * @retval none
 */
static void cmdListAlarms(void* obj, char* name,char* params)
{
	Alarm_print();
}

/**
 * @brief  cmdSetDate
 *         cmd command to set alarm date
 *         @note
 *
 *
 * @param  void* obj - the object(rtc)
 * @param  char* name - optional name
 *  @param  char* params - optional params
 * @retval none
 */
static void cmdSetDate(void* obj, char* name,char* params)
{
	Rtc* rtc = (Rtc*)obj;
	Rtc_setTime(rtc);
}

/**
 * @brief  cmdAddAlarm
 *         cmd command to add alarm
 *         @note
 *
 *
 * @param  void* obj - optional object
 * @param  char* name - the alarm name
 *  @param  char* params - alarma date
 * @retval none
 */
static void cmdAddAlarm(void* obj, char* name,char* params)
{
		DateTime dateTime;
		if(!timeStrTok(params,&dateTime)){
			printf("Incorrect time\r\n");
		}
		else if(!Alarm_add(name, dateTime)){
			printf("Alarm name already exists\r\n");
		}
}

/**
 * @brief  cmdDelAlarm
 *         cmd command to delete alarm
 *         @note
 *
 *
 * @param  void* obj - optional object
 * @param  char* name - alarm name
 *  @param  char* params - optional params
 * @retval none
 */
static void cmdDelAlarm(void* obj, char* name,char* params)
{

	if(!Alarm_delete(name)){
		printf("Alarm name didn't eexists\r\n");
	}

}
/**
 * @brief  cmdStopAlarm
 *         cmd command to stop the alarm
 *         @note
 *
 *
 * @param  void* obj - optional object
 * @param  char* name - alarm name
 *  @param  char* params - optional params
 * @retval none
 */
static void cmdStopAlarm(void* obj, char* name,char* params)
{
	Alarm_stop(name);
}
/**
 * @brief  cmdClearAllAlarms
 *         cmd command to delete all alaems
 *         @note
 *
 *
 * @param  void* obj - optional object
 * @param  char* name - optional name
 *  @param  char* params - optional params
 * @retval none
 */
static void cmdClearAllAlarms(void* obj, char* name,char* params)
{
	Alarm_clearAll();
}

/**
 * @brief  cmdEditAlarm
 *         cmd command to eddit the alarm
 *         @note
 *
 *
 * @param  void* obj - optional object
 * @param  char* name - alarm name
 *  @param  char* params - alarm date
 * @retval none
 */
static void cmdEditAlarm(void* obj, char* name,char* params)
{
	char copy[20];
	strcpy(copy,params);
	int num = paramStrTok(copy);
	if(num == 1){
		if(!Alarm_changeMelody(name, params)){
			printf("Alarm name didn't exists\r\n");
		}
	}
	else if(num == 2){
		printf("it is rep\r\n");
	}
	else{
		DateTime dateTime;
		if(!timeStrTok(params, &dateTime)){
			printf("Incorrect time\r\n");
		}
		else{
			Alarm_edit(name, dateTime);
		}
	}
}

/**
 * @brief  cmdListMelody
 *         cmd command to print the melody list
 *         @note
 *
 *
 * @param  void* obj - optional object
 * @param  char* name - optional name
 *  @param  char* params - optional params
 * @retval none
 */
void cmdListMelody(void* obj, char* name,char* params)
{
	Buzzer_printMelodies();
}

/**
 * @brief  Cli_init
 *         init the cliCommand
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void Cli_init(){
	Communication_register("getSeconds", &cmdGetSeconds,&rtc1);
	Communication_register("list", &cmdListAlarms, "");
	Communication_register("date", &cmdSetDate, &rtc1);
	Communication_register("add", &cmdAddAlarm,"");
	Communication_register("del", &cmdDelAlarm,"");
	Communication_register("stop", &cmdStopAlarm,"");
	Communication_register("clearall", &cmdClearAllAlarms,"");
	Communication_register("edit", &cmdEditAlarm,"");
	Communication_register("melody", &cmdListMelody,"");
}

