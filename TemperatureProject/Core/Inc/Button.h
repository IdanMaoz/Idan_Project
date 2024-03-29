/*
 * Button.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

enum ButtonState
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_PRESS,

};

class Button {
	private:
		GPIO_TypeDef* _gpioPort;
		uint16_t _gpioPin;
		ButtonState _btState;
	public:
		Button(GPIO_TypeDef* gpioPort,uint16_t gpioPin);
		void onInterrupt(uint32_t pin);
		ButtonState getState();
};

#endif /* INC_BUTTON_H_ */
