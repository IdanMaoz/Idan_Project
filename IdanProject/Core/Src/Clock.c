/*
 * Clock.c
 *
 *  Created on: 23 Jun 2022
 *      Author: student
 */

#include "Clock.h"

Clock myClock;

void ClockInit(){
	myClock.tickCount=0;

}

uint32_t ClockTick(){
	return myClock.tickCount;
}
