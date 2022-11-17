/*
 * Button.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
class Button {
	private:
		GPIO_TypeDef* _gpioPort;
		uint16_t _gpioPin;
	public:
		Button(GPIO_TypeDef* gpioPort,uint16_t gpioPin);
		void onInterrupt();
};

#endif /* INC_BUTTON_H_ */
