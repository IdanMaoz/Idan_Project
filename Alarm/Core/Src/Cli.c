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
/*static void cmdLedOn(void* obj, char* params)
{
	(void)params;
	Led* led = (Led*)obj;
	Led_On(led);

}
static void cmdLedOff(void* obj, char* params)
{
	(void)params;
	Led* led = (Led*)obj;
	Led_Off(led);
}

static void cmdLedBlink(void* obj, char* params)
{
	Led* led = (Led*)obj;
	Led_Blink(led, atoi(params));
}
static void cmdLedBrightness(void* obj, char* params)
{
	Led* led = (Led*)obj;
	Led_Brightness(led, atoi(params));
}


static void cmdBuzzerStop(void* obj, char* params)
{
	Buzzer* buzzer=(Buzzer*)obj;
	Buzzer_stop(buzzer);
}
static void cmdPrintFlash(void* obj, char* params)
{
	Flash* flash = (Flash*)obj;
	Flash_print(flash);
}*/

static void timeStrTok(char * params,DateTime* dateTime)
{
	uint16_t count = 0;
	char* token = strtok(params, ":");

	while( token != NULL ) {
		switch(count){
		case 0:
			dateTime->hours = atoi(token);
			token = strtok(NULL, ":");
			break;
		case 1:
			dateTime->min = atoi(token);
			token = strtok(NULL, "-");
			break;

		case 2:
			dateTime->sec = atoi(token);
			token = strtok(NULL, "-");
			break;
		case 3:
			dateTime->weekDay = atoi(token);
			token = strtok(NULL, "/");
			break;
		case 4:
			dateTime->day = atoi(token);
			token = strtok(NULL, "/");
			break;
		case 5:
			dateTime->month = atoi(token);
			token = strtok(NULL, "/");
			break;
		case 6:
			dateTime->year = atoi(token);
			token = strtok(NULL, "/");
			break;
		}
		count++;
	}
}



static void cmdGetSeconds(void* obj, char* name,char* params)
{
	Rtc* rtc = (Rtc*)obj;
	uint32_t sec = Rtc_getSeconds(rtc);
	printf("The sec is: %lu\r\n",sec);
}

static void cmdListAlarms(void* obj, char* name,char* params)
{
	Alarm_print();
}
static void cmdSetDate(void* obj, char* name,char* params)
{
	Rtc* rtc = (Rtc*)obj;
	Rtc_setTime(rtc);
}

static void cmdAddAlarm(void* obj, char* name,char* params)
{

	DateTime dateTime;
	timeStrTok(params,&dateTime);
	Alarm_add(name, dateTime);
}
static void cmdDelAlarm(void* obj, char* name,char* params)
{

	Alarm_delete(name);

}
static void cmdStopAlarm(void* obj, char* name,char* params)
{

}
static void cmdClearAllAlarms(void* obj, char* name,char* params)
{
	Alarm_clearAll();
}

static void cmdEditAlarm(void* obj, char* name,char* params)
{
	DateTime dateTime;
	timeStrTok(params, &dateTime);
	Alarm_edit(name, dateTime);
}


void Cli_init(){
	Communication_register("getSeconds", &cmdGetSeconds,&rtc1);
	Communication_register("list", &cmdListAlarms, "");
	Communication_register("date", &cmdSetDate, &rtc1);
	Communication_register("add", &cmdAddAlarm,"");
	Communication_register("del", &cmdDelAlarm,"");
	Communication_register("stop", &cmdStopAlarm,"");
	Communication_register("clearall", &cmdClearAllAlarms,"");
	Communication_register("edit", &cmdEditAlarm,"");
	/*Communication_register("blueOn", &cmdLedOn, &ledB);
	Communication_register("blueOff", &cmdLedOff, &ledB);
	Communication_register("blueBlink", &cmdLedBlink, &ledB);
	Communication_register("blueBrightness", &cmdLedBrightness, &ledB);

	Communication_register("redOn", &cmdLedOn, &ledR);
	Communication_register("redOff", &cmdLedOff, &ledR);
	Communication_register("redBlink", &cmdLedBlink, &ledR);
	Communication_register("redBrightness", &cmdLedBrightness, &ledR);


	Communication_register("buzzerStop", &cmdBuzzerStop, &bz1);
	Communication_register("printFlash", &cmdPrintFlash, &flash);*/

}

