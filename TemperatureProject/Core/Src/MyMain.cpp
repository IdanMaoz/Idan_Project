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
#include <cstring>
#include <stdio.h>
#include <SystemMonitoring.h>

extern TIM_HandleTypeDef htim16;

Button* btn1;
Button* btn2;
Buzzer* bz1;
SystemMonitoring* mySystem;
Led * redLed;

Dht* dht;
 void myMain(){
	redLed = new LedGpio(LED2_GPIO_Port,LED2_Pin);
	btn1 = new Button(SW1_GPIO_Port,SW1_Pin);
	btn2 = new Button(SW2_GPIO_Port,SW2_Pin);
	dht = new Dht(DHT11_GPIO_Port,  DHT11_Pin);
	bz1 = new Buzzer;
	mySystem = new SystemMonitoring;
	 //
	 HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

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
