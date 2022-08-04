/*
 * Led.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#include "Led.h"
#include "MainTimer.h"
#define MAX_BRIGHNESS_LEVEL 10

void Led_init(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	led->state = STATE_OFF;
	led->gpioPort = gpioPort;
	led->gpioPin = gpioPin;
}

void Led_On(Led* led)
{
	MainTimer_unRegister(Led_OnTimerInterrupt, led);
	led->state = STATE_FULL;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 1);


}

void Led_Off(Led* led)
{
	MainTimer_unRegister(Led_OnTimerInterrupt, led);
	led->state = STATE_OFF;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
}

void Led_Blink(Led* led, int period)
{
	MainTimer_registerCallback(Led_OnTimerInterrupt, led);
	led->state = STATE_BLINK;
	led->counter = 0;
	led->maxCounter = period;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
}

void Led_Brightness(Led* led ,int level)
{
	if (level < 0 || level > 10) {
		return;
	}
	led->state = STATE_BRIGHTNESS;
	led->counter=0;
	led->maxCounter=level;
}

void Led_OnTimerInterrupt(void* obj)
{
	Led* led=(Led*)obj;
	if (led->state == STATE_BLINK) {
		led->counter++;
		if (led->counter == led->maxCounter) {
			HAL_GPIO_TogglePin(led->gpioPort, led->gpioPin);
			led->counter = 0;
		}
	}

	if(led->state==STATE_BRIGHTNESS){
		if(led->counter==0){
			HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 1);
		}
		else if(led->counter==led->maxCounter){
			HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
		}
		led->counter=(led->counter+1)%MAX_BRIGHNESS_LEVEL;
	}
}
