/*
 * MyMain.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "myMain.h"
#include "main.h"
#include "Led.h"
#include "Button.h"
#include "CliCommand.h"
#include "CliContainer.h"
#include "Communication.h"
#include "Buzzer.h"
#include "LedGpio.h"
#include "LedPwm.h"
#include "TImerContainer.h"
#include "Dht.h"
#include "cmsis_os.h"
#include <cstring>
#include <stdio.h>
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim16;
//Led ledR(LED2_GPIO_Port,LED2_Pin);
//Led ledB(LED1_GPIO_Port,LED1_Pin);
Button btn1(SW1_GPIO_Port,SW1_Pin);
Button btn2(SW2_GPIO_Port,SW2_Pin);
Buzzer bz1;
timerContainer timerContainer;
Led * redLed;
Led * blueLed;
Dht* dht;
 void myMain(){
	 redLed = new LedGpio(LED2_GPIO_Port,LED2_Pin);
	 blueLed = new LedPwm(&htim2,TIM_CHANNEL_1);
	 dht = new Dht(DHT11_GPIO_Port,  DHT11_Pin);
	 //
	 HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	 //ledR.on();
	 //ledB.on();
	 HAL_TIM_Base_Start_IT(&htim6);
	 CliCommand::CliInit();

	 //dht->readAsync();

	 //ledR.blink(700);
	 //ledB.blink(1000);
	/* while(1){

		 if(Communication_task()){
			 Communication_handle();
		 }
	 }*/
 }

 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
	 if(htim == &htim6){
		 timerContainer.timeInterrupt();
	 }
 }

 void HAL_GPIO_EXTI_Callback(uint16_t pin)
 {
	btn1.onInterrupt(pin);
	btn2.onInterrupt(pin);
	if(dht!=NULL){
		dht->onGpioInterrupt(pin);
	}

 }
