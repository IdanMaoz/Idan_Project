/*
 * LedGpio.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "LedGpio.h"
#include "cmsis_os.h"
extern LedGpio* redLed;
LedGpio::LedGpio(GPIO_TypeDef* gpioPort,uint16_t gpioPin)
{
	_gpioPort = gpioPort;
	_gpioPin = gpioPin;
	_state = LED_STATE_OFF;
	_delay = 100;
}
void LedGpio::on()
{

	_state = LED_STATE_ON;
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_SET);
}
void LedGpio::off()
{

	_state = LED_STATE_OFF;
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);
}
void LedGpio::blink()
{
	_state = LED_STATE_BLINK;
}
LedState LedGpio::getState()
{
	return _state;
}
uint16_t LedGpio::getDelay()
{
	return _delay;
}
GPIO_TypeDef* LedGpio::getPort()
{
	return _gpioPort;
}
uint16_t LedGpio::getPin()
{
	return _gpioPin;
}
extern "C" void ledBlinkTask(void* argument)
{
	for(;;){
		if(redLed->getState() == LED_STATE_BLINK){
			HAL_GPIO_TogglePin(redLed->getPort(), redLed->getPin());
		}
		osDelay(redLed->getDelay());
	}
}

