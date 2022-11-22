/*
 * Button.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "Button.h"
#include "stdio.h"
Button::Button(GPIO_TypeDef* gpioPort,uint16_t gpioPin)
{
	_gpioPort = gpioPort;
	_gpioPin = gpioPin;
	_btState = BUTTON_STATE_NONE;
}
ButtonState Button::getState()
{
	return _btState;
}
void Button::onInterrupt(uint32_t pin)
{
	if(pin!=_gpioPin){
		return;
	}
	if (HAL_GPIO_ReadPin(_gpioPort, _gpioPin) == 0) {
		_btState = BUTTON_STATE_PRESS;
	}
	else{
		_btState = BUTTON_STATE_NONE;
	}
}
