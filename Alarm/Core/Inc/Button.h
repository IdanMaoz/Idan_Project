/*
 * Button.h
 *
 *  Created on: Oct 29, 2022
 *      Author: Idan Maoz
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"
typedef enum ButtonState_
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_PRESS,
	BUTTON_STATE_LONG_PRESS,
	BUTTON_STATE_DOUBLE_PRESS,

} ButtonState;

typedef struct Button_{
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	ButtonState btnState;
}Button;
void Button_init(Button* button, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
ButtonState Button_getState(Button* button);
#endif /* INC_BUTTON_H_ */
