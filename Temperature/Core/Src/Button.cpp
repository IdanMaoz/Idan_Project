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
}
void Button::onInterrupt()
{

	if (HAL_GPIO_ReadPin(_gpioPort, _gpioPin) == 0) {
		printf("pin %d\r\n",_gpioPin);
	}
}
