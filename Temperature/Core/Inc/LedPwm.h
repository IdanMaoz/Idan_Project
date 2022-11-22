/*
 * LedPwm.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef INC_LEDPWM_H_
#define INC_LEDPWM_H_

#include "main.h"
#include "Led.h"
class LedPwm: public Led {
private:
	TIM_HandleTypeDef* _pwm;
	uint32_t _channel;
	int _counter;
	int _maxCounter;
	LedState _state;
	int _brightness;
public:
	LedPwm(TIM_HandleTypeDef* pwm,uint32_t channel);
	void on() override;
	void off() override;
	void blink(int period) override;

};

#endif /* INC_LEDPWM_H_ */
