/*
 * Button.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#include "main.h"
#include "Button.h"
#include "MainTimer.h"


#define LONG_PRESS_MS 500


extern  TIM_HandleTypeDef htim3;



void Button_init(Button* button, ButtonName name, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	button->name = name;
	button->gpioPort = gpioPort;
	button->gpioPin = gpioPin;
	button->pressTime = 0;
	button->btState=BUTTON_STATE_NONE;
	button->waitToSecondPress=0;
	button->counter=0;
}


ButtonState  Button_getState(Button* bt)
{
	return bt->btState;
}

void Button_changeStateToNone(Button *bt)
{
	bt->btState=BUTTON_STATE_NONE;
}

void Button_onInterrupt(Button* button, uint16_t pin)
{
	if (pin == button->gpioPin) {
		if (HAL_GPIO_ReadPin(button->gpioPort, button->gpioPin) == 0) {
			button->pressTime = myClock.tickCount;
		}
		else {
			button->counter=0;
			if (myClock.tickCount - button->pressTime > LONG_PRESS_MS) {
				button->btState=BUTTON_STATE_LONG_PRESS;
			}
			else if (button->waitToSecondPress) {
				MainTimer_unRegister(Button_timerInterrupt, button);
				button->btState=BUTTON_STATE_DOUBLE_PRESS;
				button->waitToSecondPress=0;
			}
			else  {
				MainTimer_registerCallback(Button_timerInterrupt, button);
				button->waitToSecondPress = 1;
			}

		}

	}
}

void Button_timerInterrupt(void* obj)
{
	Button* button=(Button*)obj;
	if(button->waitToSecondPress){
		button->counter++;
		if(button->counter>300){
			MainTimer_unRegister(Button_timerInterrupt, button);
			button->btState=BUTTON_STATE_PRESS;
			button->waitToSecondPress=0;
		}
	}
}

void Button_resetCounter(Button* bt)
{
	bt->counter=0;
}


