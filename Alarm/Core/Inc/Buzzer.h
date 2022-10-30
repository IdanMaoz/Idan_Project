/*
 * Buzzer.h
 *
 *  Created on: Sep 15, 2022
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

enum Note_
{
	NOTE_1_C=262,
	NOTE_1_D=294,
	NOTE_1_E=330,
	NOTE_1_F=349,
	NOTE_1_G=392,
	NOTE_1_A=440,
	NOTE_1_B=494,

};

 enum Length_
 {
	LEN_1=1,
	LEN_2=2,
	LEN_4=4,
	LEN_8=8,
	LEN_16=16,


};
void Buzzer_init(Buzzer * buzzer);
void Buzzer_changeToOn(Buzzer * buzzer);
void Buzzer_changeToOff(Buzzer * buzzer);
void Buzzer_start(Buzzer * buzzer);
BuzzerState Buzzer_getState(Buzzer * buzzer);
#endif /* INC_BUZZER_H_ */
