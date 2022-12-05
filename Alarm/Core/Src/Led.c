/*
 * Led.c
 *
 *  Created on: Oct 29, 2022
 *      Author: Idan Maoz
 */

#include "Led.h"
#include "cmsis_os.h"
/**
 * @brief  Led_init
 *         init the led
 *         @note
 *
 *
 * @param  Led* led - the led
 * @param  GPIO_TypeDef* gpioPort - the port of the led
 * @param uint16_t gpioPin - the pin of the led
 * @param uint16_t delay - the led delay
 * @retval none
 */
void Led_init(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin,uint16_t delay)
{

	led->gpioPort = gpioPort;
	led->gpioPin = gpioPin;
	led->delay = delay;
	led->ledState = LED_STATE_OFF;
}

/**
 * @brief  Led_changeToBlink
 *         change led state to blink
 *         @note
 *
 *
 * @param  Led* led- the led
 * @retval none
 */
void Led_changeToBlink(Led* led){
	led->ledState = LED_STATE_BLINK;
}

/**
 * @brief  Led_changeToOff
 *         change led state to off
 *         @note
 *
 *
 * @param  Led* led- the led
 * @retval none
 */
void Led_changeToOff(Led* led){
	led->ledState = LED_STATE_OFF;
}

/**
 * @brief  Led_BlinkTask
 *         handle the blink of led
 *         @note
 *
 *
 * @param  void* argument - a potentioal argument(led)
 * @retval none
 */
void Led_blinkTask(void *argument)
{
	Led* led = (Led*)argument;
	for(;;){
		if(led->ledState == LED_STATE_BLINK){
			HAL_GPIO_TogglePin(led->gpioPort, led->gpioPin);
			osDelay(led->delay);
		}
		else if(led->ledState == LED_STATE_OFF){
			HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
		}

	}

}

