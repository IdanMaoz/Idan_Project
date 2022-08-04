/*
 * Button.h
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_


#include "main.h"
#include "Clock.h"
#include <stdint.h>

typedef enum ButtonState_
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_PRESS,
	BUTTON_STATE_LONG_PRESS,
	BUTTON_STATE_DOUBLE_PRESS,

} ButtonState;


typedef enum ButtonName_
{
	BTN_SW1,
	BTN_SW2
} ButtonName;

typedef struct  Button_
{
	ButtonName name;
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	uint32_t pressTime;
	ButtonState btState;
	int counter;
	int waitToSecondPress;

} Button;



void Button_init(Button* button, ButtonName name, GPIO_TypeDef* gpioPort, uint16_t gpioPin);

void Button_onInterrupt(Button* button, uint16_t pin);

ButtonState Button_getState();

void Button_changeStateToNone(Button *bt);

void Button_timerInterrupt(void* obj);


void Button_resetCounter(Button* bt);

#endif /* INC_BUTTON_H_ */
