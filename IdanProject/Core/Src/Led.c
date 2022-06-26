/*
 * Led.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#include "Led.h"

void ledInit(LED* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	led->state = STATE_OFF;
	led->gpioPort = gpioPort;
	led->gpioPin = gpioPin;
}

void ledOn(LED* led)
{
	led->state = STATE_FULL;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 1);

}

void ledOff(LED* led)
{
	led->state = STATE_OFF;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
}

void ledBlink(LED* led, int period)
{
	led->state = STATE_BLINK;
	led->counter = 0;
	led->maxCounter = period;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
}

void ledOnTimerInterrupt(LED* led)
{
	if (led->state == STATE_BLINK) {
		led->counter++;
		if (led->counter == led->maxCounter) {
			HAL_GPIO_TogglePin(led->gpioPort, led->gpioPin);
			led->counter = 0;
		}
	}
}
