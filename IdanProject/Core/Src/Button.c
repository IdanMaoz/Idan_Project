/*
 * Button.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#include "main.h"
#include "Button.h"


#define LONG_PRESS_MS 500


extern  TIM_HandleTypeDef htim3;



void buttonInit(Button* button, ButtonName name, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	button->name = name;
	button->gpioPort = gpioPort;
	button->gpioPin = gpioPin;
	button->pressTime = 0;
	button->btState=BUTTON_STATE_NONE;
}


Button_STATE  getButtonState(Button* bt)
{
	return bt->btState;
}

void changeButtonStateToNone(Button *bt){
	bt->btState=BUTTON_STATE_NONE;
}

void buttonOnInterrupt(Button* button, uint16_t pin)
{
	if (pin == button->gpioPin) {
		if (HAL_GPIO_ReadPin(button->gpioPort, button->gpioPin) == 0) {
			button->pressTime = HAL_GetTick();
		}
		else {
			if (HAL_GetTick() - button->pressTime > LONG_PRESS_MS) {
				button->btState=BUTTON_STATE_LONG_PRESS;

			}
			else {
				button->btState=BUTTON_STATE_PRESS;
			}
		}

	}
}
