

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h>
#include <main.h>
#include "LedState.h"



typedef struct Led_
{
	LedState state;
	int counter;
	int maxCounter;
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
} Led;

void Led_init(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
void Led_On(Led* led);
void Led_Off(Led* led);
void Led_Blink(Led* led, int period);
void Led_OnTimerInterrupt(Led* led);
void Led_OnPeriodicTask(Led* led);
void Led_Brightness(Led* led ,int level);

#endif /* INC_LED_H_ */
