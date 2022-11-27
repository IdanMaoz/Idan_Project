/*
 * LedPwm.h
 *
 *  Created on: 25 בנוב׳ 2022
 *      Author: Idan Maoz
 */

#ifndef INC_LEDPWM_H_
#define INC_LEDPWM_H_
#include "main.h"
#include "Led.h"
class LedPwm : public Led{
private:
	TIM_HandleTypeDef* _pwm;
	uint32_t _channel;
	int _counter;
	int _maxCounter;
	LedState _state;

public:
	LedPwm(TIM_HandleTypeDef* pwm,uint32_t channel);
	void on() override;
	void off() override;
	void blink() override;
	LedState getState() override;
	TIM_HandleTypeDef* getPwm();
	uint16_t getChannel();
	void setConter(int counter);
	int getCounter();
	int getMaxCounter();
};

#endif /* INC_LEDPWM_H_ */
