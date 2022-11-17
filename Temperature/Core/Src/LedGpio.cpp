/*
 * LedGpio.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "LedGpio.h"
#include "timerContainer.h"
extern timerContainer timerContainer;
LedGpio::LedGpio(GPIO_TypeDef* gpioPort,uint16_t gpioPin)
{
	_gpioPort = gpioPort;
	_gpioPin = gpioPin;
	_state = STATE_OFF;
	_counter  = 0;
	_maxCounter = 0;

}

void LedGpio::on()
{
	timerContainer.remove(this);
	_state = STATE_ON;
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_SET);
}
void LedGpio::off()
{
	timerContainer.remove(this);
	_state = STATE_OFF;
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);
}
void LedGpio::blink(int period)
{
	timerContainer.add(this);
	_state = STATE_BLINK;
	_counter = 0;
	_maxCounter = period;
	HAL_GPIO_WritePin(_gpioPort, _gpioPin,  GPIO_PIN_SET);
}

void LedGpio::timerFunc()
{
	if(_state == STATE_BLINK){
		_counter++;
		if (_counter == _maxCounter) {
			HAL_GPIO_TogglePin(_gpioPort, _gpioPin);
			_counter = 0;
		}
	}

}
