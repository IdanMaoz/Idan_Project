/*
 * Buzzer.c
 *
 *  Created on: Sep 15, 2022
 *      Author: student
 */

#include "Buzzer.h"
#include "cmsis_os.h"
static int _index=0;
static int _reload=0;
static const int _notes[] = {NOTE_1_G, NOTE_1_E, NOTE_1_E, NOTE_1_F, NOTE_1_D, NOTE_1_D, NOTE_1_C, NOTE_1_D, NOTE_1_E,
		NOTE_1_F, NOTE_1_G, NOTE_1_G, NOTE_1_G};
static const int _lengths[] = {LEN_4, LEN_4, LEN_2, LEN_4, LEN_4, LEN_2, LEN_4, LEN_4, LEN_4, LEN_4, LEN_4, LEN_4, LEN_2};
static const int _len=sizeof(_notes)/sizeof(_notes[_index]);
extern  TIM_HandleTypeDef htim3;
void Buzzer_init(Buzzer * buzzer)
{

	buzzer->counter=0;
	buzzer->maxCounter=1000/_lengths[0];
	buzzer->bzState=BUZZER_STATE_OFF;

}
void Buzzer_changeToOn(Buzzer * buzzer)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	buzzer->bzState=BUZZER_STATE_ON;

}
void Buzzer_changeToOff(Buzzer * buzzer)
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	buzzer->bzState=BUZZER_STATE_OFF;

}
void Buzzer_playTask(void* argument)
{
	Buzzer* buzzer = (Buzzer*)argument;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	for(;;){
		if (buzzer->bzState == BUZZER_STATE_ON){
			_reload=(100000/_notes[_index])-1;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			__HAL_TIM_SET_AUTORELOAD(&htim3, _reload);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, _reload/2);

			if(_index==(_len-1)){
				buzzer->bzState = BUZZER_STATE_OFF;
				HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
				_index = 0;
			}
			else{
				_index++;
			}



		}
			osDelay(1000/_lengths[_index]);
	}




}
