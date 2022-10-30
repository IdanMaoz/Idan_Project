/*
 * Led.c
 *
 *  Created on: Oct 29, 2022
 *      Author: Idan Maoz
 */

#include "Led.h"
#include "cmsis_os.h"
void Led_init(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin,uint16_t delay)
{

	led->gpioPort = gpioPort;
	led->gpioPin = gpioPin;
	led->delay = delay;
	led->ledState = LED_STATE_OFF;
}
void Led_changeToBlink(Led* led){
	led->ledState = LED_STATE_BLINK;
}
void Led_changeToOff(Led* led){
	led->ledState = LED_STATE_OFF;
}
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

