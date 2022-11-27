/*
 * LedPwm.cpp
 *
 *  Created on: 25 בנוב׳ 2022
 *      Author: Idan Maoz
 */

#include "LedPwm.h"
extern LedPwm* blueLed;
LedPwm::LedPwm(TIM_HandleTypeDef* pwm,uint32_t channel)
{
	_pwm =pwm;
	_channel = channel;
	_counter = 0;
	_maxCounter = 0;
	_state = LED_STATE_OFF;

}

void LedPwm::on()
{
	_state = LED_STATE_ON;
	HAL_TIM_Base_Start(_pwm);
	HAL_TIM_PWM_Start(_pwm,_channel);
	__HAL_TIM_SET_COMPARE(_pwm,_channel,100);
}
void LedPwm::off()
{


	_state = LED_STATE_OFF;
	HAL_TIM_Base_Stop(_pwm);
	HAL_TIM_PWM_Stop(_pwm,_channel);
}
void LedPwm::blink()
{
	_state = LED_STATE_BLINK;
	_counter = 0;
	_maxCounter = 100;
	HAL_TIM_Base_Start(_pwm);
	HAL_TIM_PWM_Start(_pwm, _channel);
}
LedState LedPwm::getState()
{
	return _state;
}
void LedPwm::setConter(int counter)
{
	_counter = counter;
}
int LedPwm::getCounter()
{
	return _counter;
}
int LedPwm::getMaxCounter()
{
	return _maxCounter;
}
TIM_HandleTypeDef* LedPwm::getPwm(){
	return _pwm;
}
uint16_t LedPwm::getChannel()
{
	return _channel;
}

/*extern "C" void ledBlinkTask(void* argument)
{
	if (blueLed->getState() == LED_STATE_BLINK) {
		blueLed->setConter(blueLed->getCounter()+1);
		if (blueLed->getCounter() == blueLed->getMaxCounter()) {

			if (__HAL_TIM_GET_COMPARE(blueLed->getPwm(), blueLed->getChannel()) == 0) {
				__HAL_TIM_SET_COMPARE(blueLed->getPwm(), blueLed->getChannel(), 100);
			}
			else {
				__HAL_TIM_SET_COMPARE(blueLed->getPwm(), blueLed->getChannel(), 0);
			}

			blueLed->setConter(0);
		}
	}
}*/
