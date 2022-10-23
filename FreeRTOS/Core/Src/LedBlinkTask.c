/*
 * LedBlinkTask.c
 *
 *  Created on: Sep 13, 2022
 *      Author: student
 */

#include "LedBlinkTask.h"
#include "main.h"

#include "cmsis_os.h"
//static uint32_t delay = 150;

void Led_init(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{

	led->gpioPort = gpioPort;
	led->gpioPin = gpioPin;
	led->delay = 500;
}

void Led_blinkTask(void *argument)
{
	Led* led = (Led*)argument;
	for(;;){
		//HAL_GPIO_TogglePin(led->gpioPort, led->gpioPin);
		osDelay(led->delay);
	}

}

void Led_setDelay(Led* led,uint32_t value)
{

	led->delay = value;

}
