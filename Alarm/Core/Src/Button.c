/*
 * Button.c
 *
 *  Created on: Oct 29, 2022
 *      Author: Idan Maoz
 */

#include "Button.h"
#include "stdio.h"
void Button_init(Button* button, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{

	button->gpioPort = gpioPort;
	button->gpioPin = gpioPin;
	button->btnState = BUTTON_STATE_NONE;
}
ButtonState Button_getState(Button* button){
	return button->btnState;
}
void Button_pressTask(void *argument)
{
	Button* btn = (Button*)argument;
	for(;;){
		if(HAL_GPIO_ReadPin(btn->gpioPort, btn->gpioPin) == 0){

			btn->btnState = BUTTON_STATE_PRESS;
		}
		else{
			btn->btnState = BUTTON_STATE_NONE;
		}
	}

}
