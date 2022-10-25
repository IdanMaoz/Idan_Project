/*
 * Mymain.c
 *
 *  Created on: Oct 23, 2022
 *      Author: student
 */

#include "MyMain.h"
#include "main.h"
#include "Communication.h"
#include "Cli.h"
#include "Buzzer.h"
#include "Rtc.h"
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;
Buzzer bz1;
Rtc rtc1;
void MyMain()
{
	printf("----------Commands List----------\r\n");
	printf("1.Command \033[33mlist \033[0m to print all existing alarms.\r\n");
	printf("2.Command \033[33mdate hours:min:sec-weekDay-day/month/year\033[0m to sets the current date.\r\n");
	printf("3.Command \033[33mAdd alarmName hours:min:sec-weekDay-day/month/year\033[0m to add a new alarm.\r\n");
	printf("4.Command \033[33mdel alarmName\033[0m to delete current alarm.\r\n");
	printf("5.Command \033[33mstop alarmName\033[0m to stop current alarm.\r\n");
	printf("6.Command \033[33msnooze alarmName\033[0m to snooze current alarm.\r\n");
	printf("7.Command \033[33mclearall\033[0m to remove all alarms.\r\n");
	printf("8.Command \033[33medit alarmName hours:min:sec-weekDay-day/month/year\033[0m to edit alarm.\r\n");
	printf("9.Command \033[33mmelody \033[0m to print all all available melodies.\r\n");
	printf("---------------------------------\r\n");



	Cli_init();
	Rtc_init(&rtc1, &hi2c1, 0xD0);
	Rtc_setTime(&rtc1);
	Buzzer_init(&bz1);


}
