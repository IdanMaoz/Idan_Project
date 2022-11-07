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
#include "Alarm.h"
#include "Led.h"
#include <stdio.h>
#include "Flash.h"
extern I2C_HandleTypeDef hi2c1;
Buzzer bz1;
Rtc rtc1;
Led ledR;
Led ledB;
Button btn1;
Button btn2;
void MyMain()
{
	printf("----------Commands List----------\r\n");
	printf(" 1.Command \033[33mlist \033[0m to print all existing alarms.\r\n");
	printf(" 2.Command \033[33mdate hours:min:sec-weekDay-day/month/year\033[0m to sets the current date.\r\n");
	printf(" 3.Command \033[33madd alarmName hours:min:sec-weekDay-day/month/year\033[0m to add alarm.\r\n");
	printf(" 4.Command \033[33mdel alarmName\033[0m to delete current alarm.\r\n");
	printf(" 5.Command \033[33mstop alarmName\033[0m to stop current alarm.\r\n");
	printf(" 6.Command \033[33msnooze alarmName\033[0m to snooze current alarm.\r\n");
	printf(" 7.Command \033[33mclearall\033[0m to remove all alarms.\r\n");
	printf(" 8.Command \033[33medit alarmName hours:min:sec-weekDay-day/month/year\033[0m to edit time.\r\n");
	printf(" 9.Command \033[33medit alarmName melodyNumber\033[0m to edit melody.\r\n");
	printf("10.Command \033[33medit alarmName repNumber\033[0m to edit repetetion.\r\n");
	printf("11.Command \033[33melody \033[0m to print all all available melodies.\r\n");
	printf("---------------------------------\r\n");



	Alarm_flashToAlarms();
	Cli_init();
	Rtc_init(&rtc1, &hi2c1, 0xD0);
	Rtc_setTime(&rtc1);
	Buzzer_init(&bz1);
	Led_init(&ledR, LED2_GPIO_Port, LED2_Pin,50);
	Led_init(&ledB, LED1_GPIO_Port, LED1_Pin,300);
	Button_init(&btn1, SW1_GPIO_Port, SW1_Pin);
	Button_init(&btn2, SW2_GPIO_Port, SW2_Pin);

}
