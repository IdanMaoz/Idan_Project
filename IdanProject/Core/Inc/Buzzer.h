/*
 * Buzzer.h
 *
 *  Created on: 23 Jun 2022
 *      Author: student
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_


#include "main.h"
#include <stdint.h>

typedef enum BuzzerState_
{
	BUZZER_STATE_OFF,
	BUZZER_STATE_ON,

} BuzzerState;

typedef struct  Buzzer_
{

	int counter;
	int maxCounter;
	BuzzerState bzState;

} Buzzer;



void Buzzer_init(Buzzer * buzzer);
void Buzzer_interrupt(void * obj);
void Buzzer_reset();
void Buzzer_changeToOn(Buzzer * buzzer);
void Buzzer_changeToOff(Buzzer * buzzer);
void Buzzer_stop(Buzzer * buzzer);
void Buzzer_start(Buzzer * buzzer);
#endif /* INC_BUZZER_H_ */
