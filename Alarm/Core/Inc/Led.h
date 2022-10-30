/*
 * Led.h
 *
 *  Created on: Oct 29, 2022
 *      Author: Idan Maoz
 */

#ifndef INC_LED_H_
#define INC_LED_H_
#include "main.h"
typedef enum LedState_
{
	LED_STATE_OFF,
	LED_STATE_ON,
	LED_STATE_BLINK,

} LedState;

typedef struct Led_
{
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	uint32_t delay;
	LedState ledState;

}Led;
void Led_init(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin,uint16_t delay);
void Led_changeToBlink(Led* led);
void Led_changeToOff(Led* led);
#endif /* INC_LED_H_ */
