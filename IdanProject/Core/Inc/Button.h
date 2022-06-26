/*
 * Button.h
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>
#include "main.h"

typedef enum ButtonState_
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_PRESS,
	BUTTON_STATE_LONG_PRESS,
	BUTTON_STATE_DOUBLE_PRESS,

} Button_STATE;


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
	Button_STATE btState;
} Button;


void buttonInit(Button* button, ButtonName name, GPIO_TypeDef* gpioPort, uint16_t gpioPin);

void buttonOnInterrupt(Button* button, uint16_t pin);

Button_STATE getButtonState();

void changeButtonStateToNone(Button *bt);

#endif /* INC_BUTTON_H_ */
