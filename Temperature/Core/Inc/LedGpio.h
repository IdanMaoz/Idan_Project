/*
 * LedGpio.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef INC_LEDGPIO_H_
#define INC_LEDGPIO_H_
#include "main.h"
#include "Led.h"
class LedGpio : public Led {
private:
	int _counter;
	int _maxCounter;
	GPIO_TypeDef* _gpioPort;
	uint16_t _gpioPin;
	LedState _state;

public:
	LedGpio(GPIO_TypeDef* gpioPort,uint16_t gpioPin);
	void on() override;
	void off() override;
	void blink(int period) override;
	virtual void timerFunc() override;
};

#endif /* INC_LEDGPIO_H_ */
