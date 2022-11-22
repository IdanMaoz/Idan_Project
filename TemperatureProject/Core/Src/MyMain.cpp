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
//#include "cmsis_os.h"
#include <cstring>
#include <stdio.h>

extern TIM_HandleTypeDef htim16;

Button btn1(SW1_GPIO_Port,SW1_Pin);
Button btn2(SW2_GPIO_Port,SW2_Pin);
Buzzer bz1;
Led * redLed;

Dht* dht;
 void myMain(){
	redLed = new LedGpio(LED2_GPIO_Port,LED2_Pin);

	 dht = new Dht(DHT11_GPIO_Port,  DHT11_Pin);
	 //
	 HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	 //HAL_TIM_Base_Start_IT(&htim6);
	 CliCommand::CliInit();


 }


 void HAL_GPIO_EXTI_Callback(uint16_t pin)
 {
	btn1.onInterrupt(pin);
	btn2.onInterrupt(pin);
	if(dht!=NULL){
		dht->onGpioInterrupt(pin);
	}

 }
