/*
 * Buzzer.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "Buzzer.h"
#include "main.h"


extern  TIM_HandleTypeDef htim3;
Buzzer::Buzzer() {
	_bzState = BUZZER_STATE_OFF;

}
void Buzzer::start()
{

	_bzState = BUZZER_STATE_ON;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim3);

}

void Buzzer::stop()
{

	_bzState = BUZZER_STATE_OFF;
	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}
