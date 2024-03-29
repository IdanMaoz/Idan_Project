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
#include "Communication.h"
#include "Rtc.h"
#include "SDCard.h"
#include "File.h"
#include <cstring>
#include <iostream>
#include <fstream>

extern TIM_HandleTypeDef htim16;
extern I2C_HandleTypeDef hi2c1;

Button* btn1;
Button* btn2;
Buzzer* bz1;
SystemMonitoring* mySystem;
Led * redLed;
Led* blueLed;
Dht* dht;
Rtc* rtc;
Flash* Flash::_instance = 0;
Flash* flash;
SDCard* sdCard;
File* tempFile;
File* eventsLogFile;
Communication* com;

 void myMain()
 {
	flash = flash->getInstance();
	redLed = new LedGpio(LED2_GPIO_Port,LED2_Pin);
	btn1 = new Button(SW1_GPIO_Port,SW1_Pin);
	btn2 = new Button(SW2_GPIO_Port,SW2_Pin);
	dht = new Dht(DHT11_GPIO_Port,  DHT11_Pin);
	bz1 = new Buzzer;
	mySystem = new SystemMonitoring;
	rtc = new Rtc(&hi2c1,0XD0);
	sdCard = new SDCard;
	sdCard->openSystem();
	tempFile = new File("tempFile.txt");
	eventsLogFile = new File("logFile.txt");
	com = new Communication;
	printf("Supported Commands:\r\n");
	printf("warning [number]\r\n"
			"critical [number]\r\n"
			"date [hours:minutes:seconds-dayInWeek-day/month/year]\r\n"
			"print\r\n"
			"clear\r\n\r\n");
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

