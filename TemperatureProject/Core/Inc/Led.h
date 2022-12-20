/*
 * Led.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

enum LedState
{
	LED_STATE_ON,
	LED_STATE_OFF,
	LED_STATE_BLINK,
};

class Led {
public:
	~Led(){};
	virtual void on() = 0;
	virtual void off() = 0;
	virtual void blink() = 0;
	virtual LedState getState() = 0;
};

#endif /* INC_LED_H_ */
