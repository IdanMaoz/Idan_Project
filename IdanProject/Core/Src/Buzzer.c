/*
 * Buzzer.c
 *
 *  Created on: 23 Jun 2022
 *      Author: student
 */

#include "Buzzer.h"
#include "music.h"
#include "main.h"
#include "MainTimer.h"
#include <stdio.h>

extern  TIM_HandleTypeDef htim3;


static int _index=0;
static int _reload=0;
static const int _notes[] = {NOTE_1_G, NOTE_1_E, NOTE_1_E, NOTE_1_F, NOTE_1_D, NOTE_1_D, NOTE_1_C, NOTE_1_D, NOTE_1_E,
		NOTE_1_F, NOTE_1_G, NOTE_1_G, NOTE_1_G};
static const int _lengths[] = {LEN_4, LEN_4, LEN_2, LEN_4, LEN_4, LEN_2, LEN_4, LEN_4, LEN_4, LEN_4, LEN_4, LEN_4, LEN_2};
static const int _len=sizeof(_notes)/sizeof(_notes[_index]);

void Buzzer_init(Buzzer * buzzer)
{

	buzzer->counter=0;
	buzzer->maxCounter=1000/_lengths[0];
	buzzer->bzState=BUZZER_STATE_OFF;

}


void Buzzer_interrupt(void* obj)
{
	Buzzer* buzzer=(Buzzer*)obj;
	if(buzzer->bzState !=BUZZER_STATE_ON){
		return;
	}

	buzzer->counter++;
	if (buzzer->counter < buzzer->maxCounter) {
		return;
	}
	_reload=(100000/_notes[_index])-1;
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim3, _reload);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, _reload/2);

	if(_index==(_len-1)){
		_index=0;
	}
	else{
		_index++;
	}

	buzzer->maxCounter=1000/_lengths[_index];
	buzzer->counter=0;

}

void Buzzer_changeToOn(Buzzer * buzzer)
{
	buzzer->bzState=BUZZER_STATE_ON;

}

void Buzzer_changeToOff(Buzzer * buzzer)
{
	buzzer->bzState=BUZZER_STATE_OFF;

}


void Buzzer_reset()
{
	_index=0;

}

void Buzzer_stop(Buzzer* buzzer)
{
	Buzzer_changeToOff(buzzer);
	MainTimer_unRegister(Buzzer_interrupt, buzzer);
	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

void Buzzer_start(Buzzer* buzzer)
{
	Buzzer_changeToOn(buzzer);
	MainTimer_registerCallback(Buzzer_interrupt,buzzer);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim3);
}


