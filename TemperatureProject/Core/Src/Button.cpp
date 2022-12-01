
#include "Button.h"
#include "stdio.h"
/**
 * @brief  Button
 *         init the button
 *         @note
 *
 *
 * @param  GPIO_TypeDef* gpioPort - the port of the button
 * @param uint16_t gpioPin - the pin of the button
 * @retval none
 */
Button::Button(GPIO_TypeDef* gpioPort,uint16_t gpioPin)
{
	_gpioPort = gpioPort;
	_gpioPin = gpioPin;
	_btState = BUTTON_STATE_NONE;
}

/**
 * @brief  getState
 *         get the state of the button
 *         @note
 *
 *
 * @param  none
 * @retval the state of button
 */
ButtonState Button::getState()
{
	return _btState;
}

/**
 * @brief  onInterrupt
 *         change the button state if user pressed
 *         @note
 *
 *
 * @param uint16_t pin - the pin of the button
 * @retval none
 */
void Button::onInterrupt(uint32_t pin)
{
	if(pin!=_gpioPin){
		return;
	}
	if (HAL_GPIO_ReadPin(_gpioPort, _gpioPin) == 0) {
		_btState = BUTTON_STATE_PRESS;
	}
	else{
		_btState = BUTTON_STATE_NONE;
	}
}
