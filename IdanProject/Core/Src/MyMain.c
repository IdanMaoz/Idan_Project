
#include "MyMain.h"
#include "main.h"
#include "Button.h"
#include "Led.h"
#include "Clock.h"
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

	 ClockInit();

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
				 stopBuzzer();
				 printf("SW1 short press\n\r");
				 changeButtonStateToNone(&buttonSw1);
				 changeBuzzerToOff(&bz1);
				 break;


			 case BUTTON_STATE_LONG_PRESS:

				 //HAL_TIM_Base_Start_IT(&htim6);
				 startBuzzer();
				 printf("SW1 long press\n\r");
				 changeButtonStateToNone(&buttonSw1);
				 changeBuzzerToOn(&bz1);
				 break;

			 case BUTTON_STATE_DOUBLE_PRESS:
				 printf("SW1 double press\n\r");
				 ledBlink(&ledB, 100);
				 ledBlink(&ledR, 500);
				 changeButtonStateToNone(&buttonSw1);
			 case BUTTON_STATE_NONE:
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
		 		ledBlink(&ledB, 500);
		 		ledBlink(&ledR, 100);
		 		printf("SW2 double press\n\r");
		 		changeButtonStateToNone(&buttonSw2);
		 		break;
		 	case BUTTON_STATE_NONE:
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

		myClock.tickCount++;
		buttonTimerInterrupt(&buttonSw1);
		buttonTimerInterrupt(&buttonSw2);




	}
}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	buttonOnInterrupt(&buttonSw1, pin);
	buttonOnInterrupt(&buttonSw2, pin);
	resetBuzzer();





}



