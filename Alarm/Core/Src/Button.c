/*
 * Button.c
 *
 *  Created on: Oct 29, 2022
 *      Author: Idan Maoz
 */

#include "Button.h"
#include "stdio.h"

/**
 * @brief  Button_init
 *         init the button
 *         @note
 *
 *
 * @param Button* button - the button
 * @param  GPIO_TypeDef* gpioPort - the port of the button
 * @param uint16_t gpioPin - the pin of the button
 * @retval none
 */
void Button_init(Button* button, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{

	button->gpioPort = gpioPort;
	button->gpioPin = gpioPin;
	button->btnState = BUTTON_STATE_NONE;
}

/**
 * @brief  Button_getState
 *         get the state of the button
 *         @note
 *
 *
 * @param  Button* button - the button
 * @retval the state of button
 */
ButtonState Button_getState(Button* button){
	return button->btnState;
}

/**
 * @brief  Button_pressTask
 *         handle the button press
 *         @note
 *
 *
 * @param void* argument - a potential argument
 * @retval none
 */
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
