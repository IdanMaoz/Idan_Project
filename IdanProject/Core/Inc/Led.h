

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h>
#include <main.h>
#include "LedState.h"



typedef struct Led_
{
	LED_STATE state;
	int counter;
	int maxCounter;
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
} LED;

void ledInit(LED* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
void ledOn(LED* led);
void ledOff(LED* led);
void ledBlink(LED* led, int period);
void ledOnTimerInterrupt(LED* led);
void ledOnPeriodicTask(LED* led);


#endif /* INC_LED_H_ */
