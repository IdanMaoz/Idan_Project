/*
 * MyMain.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "MyMain.h"
#include "main.h"
#include "Dht.h"
#include "Led.h"
#include "Buzzer.h"
#include "LedGpio.h"
#include "Button.h"
#include "CliCommand.h"
#include "SystemMonitoring.h"
#include "Flash.h"
#include "Rtc.h"
#include <cstring>
#include <stdio.h>
#include <iostream>


extern TIM_HandleTypeDef htim16;
extern I2C_HandleTypeDef hi2c1;
Button* btn1;
Button* btn2;
Buzzer* bz1;
SystemMonitoring* mySystem;
Led * redLed;
#include <iostream>
#include <fstream>
Dht* dht;
Rtc* rtc;
Flash* flash;
void setTime(DateTime* dateTime)
{
	dateTime->sec = 0;
	dateTime->min = 7;
	dateTime->hours = 16;
	dateTime->weekDay = 5;
	dateTime->day = 24;
	dateTime->month = 11;
	dateTime->year = 22;


}
 void myMain()
 {
	flash = new Flash;
	redLed = new LedGpio(LED2_GPIO_Port,LED2_Pin);
	btn1 = new Button(SW1_GPIO_Port,SW1_Pin);
	btn2 = new Button(SW2_GPIO_Port,SW2_Pin);
	dht = new Dht(DHT11_GPIO_Port,  DHT11_Pin);
	bz1 = new Buzzer;
	mySystem = new SystemMonitoring;
	rtc = new Rtc(&hi2c1,0XD0);




	 //HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	 //HAL_TIM_Base_Start_IT(&htim6);
	 CliCommand::CliInit();



}


 void HAL_GPIO_EXTI_Callback(uint16_t pin)
 {
	btn1->onInterrupt(pin);
	btn2->onInterrupt(pin);
	if(dht!=NULL){
		dht->onGpioInterrupt(pin);
	}
 }
