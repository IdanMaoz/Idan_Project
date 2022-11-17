/*
 * LedPwm.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "LedPwm.h"
#include "main.h"
#include "TImerContainer.h"
extern timerContainer timerContainer;
extern  TIM_HandleTypeDef htim2;
LedPwm::LedPwm(TIM_HandleTypeDef* pwm,uint32_t channel)
{
	_pwm =pwm;
	_channel = channel;
	_counter = 0;
	_maxCounter = 0;
	_state = STATE_OFF;
	_brightness = 100;

}

void LedPwm::on()
{
	timerContainer.remove(this);
	_state = STATE_ON;
	HAL_TIM_Base_Start(_pwm);
	HAL_TIM_PWM_Start(_pwm,_channel);
	__HAL_TIM_SET_COMPARE(_pwm,_channel,_brightness);
}
void LedPwm::off()
{

	timerContainer.remove(this);
	_state = STATE_OFF;
	HAL_TIM_Base_Stop(_pwm);
	HAL_TIM_PWM_Stop(_pwm,_channel);
}
void LedPwm::blink(int period)
{
	timerContainer.add(this);
	_state = STATE_BLINK;
	_counter = 0;
	_maxCounter = period;
	HAL_TIM_Base_Start(_pwm);
	HAL_TIM_PWM_Start(_pwm, _channel);
}
void LedPwm::timerFunc()
{
	if (_state == STATE_BLINK) {
		_counter++;
		if (_counter == _maxCounter) {

			if (__HAL_TIM_GET_COMPARE(_pwm, _channel) == 0) {
				__HAL_TIM_SET_COMPARE(_pwm, _channel, _brightness);
			}
			else {
				__HAL_TIM_SET_COMPARE(_pwm, _channel, 0);
			}

			_counter = 0;
		}
	}
}


