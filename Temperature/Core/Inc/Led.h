/*
 * Led.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef INC_LED_H_
#define INC_LED_H_
#include "TimerTask.h"
#include "main.h"
typedef enum LedState_
{
	STATE_ON,
	STATE_OFF,
	STATE_BLINK,
	STATE_BRIGHTNESS,
} LedState;

class Led : public TimerTask{
	public:
		~Led(){};
		virtual void on() = 0;
		virtual void off() = 0;
		virtual void blink(int period) = 0;
		virtual void timerFunc() = 0;
};
#endif /* INC_LED_H_ */
