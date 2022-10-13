
#include <Cli.h>
#include <Communication.h>
#include <stdio.h>

#include "MyMain.h"
#include "main.h"
#include "Button.h"
#include "Led.h"
#include "Clock.h"
#include "music.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "Dht.h"
#include "MainTimer.h"
#include "Flash.h"

extern TIM_HandleTypeDef htim6;
extern  TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc2;

Led ledB;
Led ledR;

Button buttonSw1;
Button buttonSw2;

Buzzer bz1;

FlashData flashData;
LightSensor lts1;

Dht dht;

FLASH_EraseInitTypeDef pEraseInit;
Flash flash;

void MyMain(){
	Led_init(&ledB, LED1_GPIO_Port, LED1_Pin);
	Led_init(&ledR, LED2_GPIO_Port, LED2_Pin);

	Button_init(&buttonSw1, BTN_SW1, SW1_GPIO_Port,  SW1_Pin);
	Button_init(&buttonSw2, BTN_SW2, SW2_GPIO_Port, SW2_Pin);

	LightSensor_init(&lts1, &hadc2, 10);


	Clock_init();

	Buzzer_init(&bz1);

	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);



	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
	HAL_ADC_Start_IT(&hadc2);

	//ledBlink(&ledB, 500);
	//ledOn(&ledB);

	ButtonState SW1State;
	ButtonState SW2State;
	Cli_init();
	Dht_init(&dht, DHT11_GPIO_Port,  DHT11_Pin);
	Dht_readAsync(&dht);

	HAL_NVIC_EnableIRQ(FLASH_IRQn);


	//static char data[24] = "interrupt flash!!";
	//Flash_write((0x08080000), data, 24);
	Flash_init(&flash);

	HAL_TIM_Base_Start_IT(&htim6);
	while(1){
		if(Dht_hasData(&dht)){
			printf("The humidity is: %.2lf\r\n",Dht_getHumidity(&dht));
			printf("The temperature is: %.2lf\r\n",Dht_getTemperature(&dht));
			printf("The sum is: %d\r\n",Dht_getSum(&dht));
			Dht_changeStateToResStart(&dht);

		}
		if (Communication_task())
		{
			Communication_handle();
		}



		SW1State=Button_getState(&buttonSw1);


		if(SW1State!=BUTTON_STATE_NONE){
			switch(SW1State){
			case BUTTON_STATE_PRESS:
				//HAL_TIM_Base_Stop_IT(&htim6);
				Buzzer_stop(&bz1);
				printf("SW1 short press\n\r");
				Button_changeStateToNone(&buttonSw1);
				Buzzer_changeToOff(&bz1);
				break;


			case BUTTON_STATE_LONG_PRESS:

				//HAL_TIM_Base_Start_IT(&htim6);
				//Buzzer_start(&bz1);
				printf("SW1 long press\n\r");
				Button_changeStateToNone(&buttonSw1);
				//Buzzer_changeToOn(&bz1);
				break;

			case BUTTON_STATE_DOUBLE_PRESS:
				printf("SW1 double press\n\r");
				Led_Blink(&ledB, 100);
				Led_Blink(&ledR, 500);
				Button_changeStateToNone(&buttonSw1);
			case BUTTON_STATE_NONE:
				break;

			}
		}

		SW2State=Button_getState(&buttonSw2);
		if(SW2State!=BUTTON_STATE_NONE){
			switch(SW2State){
			case BUTTON_STATE_PRESS:
				Led_On(&ledR);
				Led_On(&ledB);
				printf("SW2 short press\n\r");
				Button_changeStateToNone(&buttonSw2);
				break;
			case BUTTON_STATE_LONG_PRESS:

				Led_Off(&ledR);
				Led_Off(&ledB);
				printf("SW2 long press\n\r");
				Button_changeStateToNone(&buttonSw2);
				break;

			case BUTTON_STATE_DOUBLE_PRESS:
				Led_Brightness(&ledR, 2);
				Led_Brightness(&ledB, 5);
				printf("SW2 double press\n\r");
				Button_changeStateToNone(&buttonSw2);
				break;
			case BUTTON_STATE_NONE:
				break;

			}

		}

	}

}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	Button_onInterrupt(&buttonSw1, pin);
	Button_onInterrupt(&buttonSw2, pin);
	Buzzer_reset();
	Dht_onGpioInterrupt(&dht,pin);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	LightSensor_adcInterrupt(&lts1);
}




