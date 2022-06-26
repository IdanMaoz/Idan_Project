/*
 * Buzzer.c
 *
 *  Created on: 23 Jun 2022
 *      Author: student
 */

#include "Buzzer.h"
#include "music.h"
#include "main.h"
#include <stdio.h>

extern  TIM_HandleTypeDef htim3;


int i=0;
int reload=0;
const int Notes[] = {NOTE_1_G, NOTE_1_E, NOTE_1_E, NOTE_1_F, NOTE_1_D, NOTE_1_D, NOTE_1_C, NOTE_1_D, NOTE_1_E, NOTE_1_F, NOTE_1_G, NOTE_1_G, NOTE_1_G};
const int Lengths[] = {LEN_4, LEN_4, LEN_2, LEN_4, LEN_4, LEN_2, LEN_4, LEN_4, LEN_4, LEN_4, LEN_4, LEN_4, LEN_2};
int len=sizeof(Notes)/sizeof(Notes[i]);

void buzzerInit(Buzzer * buzzer)
{


	buzzer->counter=0;
	buzzer->maxCounter=1000/Lengths[0];
	buzzer->bzState=BUZZER_STATE_OFF;

}


void BuzzerInterrupt(Buzzer * buzzer){

	if(buzzer->bzState !=BUZZER_STATE_ON){
		return;
	}
	buzzer->counter++;
	if (buzzer->counter < buzzer->maxCounter) {
		return;
	}

	reload=(100000/Notes[i])-1;
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim3, reload);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, reload/2);

	if(i==(len-1)){
		i=0;
	}
	else{
		i++;
	}

	buzzer->maxCounter=1000/Lengths[i];
	buzzer->counter=0;

}

void changeBuzzerToOn(Buzzer * buzzer){
	buzzer->bzState=BUZZER_STATE_ON;

}

void changeBuzzerToOff(Buzzer * buzzer){
	buzzer->bzState=BUZZER_STATE_OFF;

}


void resetBuzzer(){
	i=0;

}

void stopBuzzer(){

	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

void startBuzzer(){
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim3);

}


