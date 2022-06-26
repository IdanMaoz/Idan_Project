/*
 * Buzzer.h
 *
 *  Created on: 23 Jun 2022
 *      Author: student
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <stdint.h>
#include "main.h"

typedef enum BuzzerState_
{
	BUZZER_STATE_OFF,
	BUZZER_STATE_ON,

} Buzzer_STATE;

typedef struct  Buzzer_
{

	int counter;
	int maxCounter;
	Buzzer_STATE bzState;

} Buzzer;



void buzzerInit(Buzzer * buzzer);
void BuzzerInterrupt();
void resetBuzzer();
void changeBuzzerToOn(Buzzer * buzzer);
void changeBuzzerToOff(Buzzer * buzzer);
#endif /* INC_BUZZER_H_ */
