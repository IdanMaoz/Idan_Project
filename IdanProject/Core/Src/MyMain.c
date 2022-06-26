
#include "MyMain.h"
#include "main.h"
#include "Button.h"
#include "Led.h"
#include "InputControl.h"
#include "music.h"
#include "Buzzer.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim6;
extern  TIM_HandleTypeDef htim3;

LED ledB;
LED ledR;

Button buttonSw1;
Button buttonSw2;

Buzzer bz1;


void Mymain(){
	ledInit(&ledB, LED1_GPIO_Port, LED1_Pin);
	ledInit(&ledR, LED2_GPIO_Port, LED2_Pin);

	 buttonInit(&buttonSw1, BTN_SW1, SW1_GPIO_Port,  SW1_Pin);
	 buttonInit(&buttonSw2, BTN_SW2, SW2_GPIO_Port, SW2_Pin);

	 buzzerInit(&bz1);

	 HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	 HAL_TIM_Base_Start_IT(&htim6);

	 //ledBlink(&ledB, 10);
	 //ledOn(&ledB);

	 Button_STATE SW1State;
	 Button_STATE SW2State;
	 while(1){
		 SW1State=getButtonState(&buttonSw1);


		 if(SW1State!=BUTTON_STATE_NONE){
			 switch(SW1State){
			 case BUTTON_STATE_PRESS:
				 //HAL_TIM_Base_Stop_IT(&htim6);
				 HAL_TIM_Base_Stop_IT(&htim3);
				 HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
				 printf("SW1 short press\n\r");
				 changeButtonStateToNone(&buttonSw1);
				 changeBuzzerToOff(&bz1);
				 break;


			 case BUTTON_STATE_LONG_PRESS:

				 //HAL_TIM_Base_Start_IT(&htim6);
				 HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
				 HAL_TIM_Base_Start_IT(&htim3);
				 printf("SW1 long press\n\r");
				 changeButtonStateToNone(&buttonSw1);
				 changeBuzzerToOn(&bz1);
				 break;

			 case BUTTON_STATE_DOUBLE_PRESS:
				 break;
			 }
		 }

		 SW2State=getButtonState(&buttonSw2);
		 if(SW2State!=BUTTON_STATE_NONE){
		 	switch(SW2State){
		 	case BUTTON_STATE_PRESS:
		 		ledOn(&ledR);
		 		ledOn(&ledB);
		 		printf("SW2 short press\n\r");
		 		changeButtonStateToNone(&buttonSw2);
		 		break;
		 	case BUTTON_STATE_LONG_PRESS:

		 		ledOff(&ledR);
		 		ledOff(&ledB);
		 		printf("SW2 long press\n\r");
		 		changeButtonStateToNone(&buttonSw2);
		 		break;

		 	case BUTTON_STATE_DOUBLE_PRESS:
		 		break;
		 	}
		 }

	 }

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim6){


		ledOnTimerInterrupt(&ledB);
		ledOnTimerInterrupt(&ledR);


		BuzzerInterrupt(&bz1);



	}
}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	buttonOnInterrupt(&buttonSw1, pin);
	buttonOnInterrupt(&buttonSw2, pin);
	resetBuzzer();

}



