/*
 * Clock.h
 *
 *  Created on: 23 Jun 2022
 *      Author: student
 */

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

#include <stdint.h>

typedef struct  Clock_
{

	uint32_t tickCount;

} Clock;

extern Clock myClock;

void Clock_init();
uint32_t Clock_getTick();





#endif /* INC_CLOCK_H_ */
