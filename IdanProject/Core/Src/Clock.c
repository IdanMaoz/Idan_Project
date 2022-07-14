/*
 * Clock.c
 *
 *  Created on: 23 Jun 2022
 *      Author: student
 */

#include "Clock.h"

Clock myClock;

void Clock_init()
{
	myClock.tickCount=0;

}

uint32_t Clock_getTick()
{
	return myClock.tickCount;
}
