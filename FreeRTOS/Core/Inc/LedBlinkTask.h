/*
 * LedBlinkTask.h
 *
 *  Created on: Sep 13, 2022
 *      Author: student
 */

#ifndef INC_LEDBLINKTASK_H_
#define INC_LEDBLINKTASK_H_
#include <stdint.h>
#include "stm32l4xx_hal.h"
typedef struct Led_
{
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	uint32_t delay;
}Led;
void Led_init(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
void Led_setDelay(Led* led,uint32_t value);


#endif /* INC_LEDBLINKTASK_H_ */
