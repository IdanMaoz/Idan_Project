/*
 * Buzzer.c
 *
 *  Created on: Sep 15, 2022
 *      Author: student
 */

#include "Buzzer.h"
#include <string.h>
#include "stdio.h"
#include "cmsis_os.h"
static int _index=0;
static int _reload=0;
static int _countBeep=0;
static int _melody = 0;
static const int _notes[] = {NOTE_1_G, NOTE_1_E, NOTE_1_E, NOTE_1_F, NOTE_1_D, NOTE_1_D, NOTE_1_C, NOTE_1_D, NOTE_1_E,
		NOTE_1_F, NOTE_1_G, NOTE_1_G, NOTE_1_G};
static const int _lengths[] = {LEN_4, LEN_4, LEN_2, LEN_4, LEN_4, LEN_2, LEN_4, LEN_4, LEN_4, LEN_4, LEN_4, LEN_4, LEN_2};
static const int _len=sizeof(_notes)/sizeof(_notes[_index]);
extern  TIM_HandleTypeDef htim3;

/**
 * @brief  Buzzer_init
 *         init the buzzer
 *         @note
 *
 *
 * @param  Buzzer* buzzer - the buzzer
 * @retval none
 */
void Buzzer_init(Buzzer * buzzer)
{

	buzzer->bzState=BUZZER_STATE_OFF;

}
/**
 * @brief  Buzzer_changeToOn
 *         start the buzzer and change state to on
 *         @note
 *
 *
 * @param  Buzzer* buzzer - the buzzer
 * @retval none
 */
void Buzzer_changeToOn(Buzzer * buzzer)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	buzzer->bzState=BUZZER_STATE_ON;

}

/**
 * @brief  Buzzer_changeToOff
 *         stop the buzzer and change state to off
 *         @note
 *
 *
 * @param  Buzzer* buzzer - the buzzer
 * @retval none
 */
void Buzzer_changeToOff(Buzzer * buzzer)
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	buzzer->bzState=BUZZER_STATE_OFF;

}

/**
 * @brief  Buzzer_getState
 *         get the state of buzzer
 *         @note
 *
 *
 * @param  Buzzer* buzzer - the buzzer
 * @retval the state of buzzer
 */
BuzzerState Buzzer_getState(Buzzer * buzzer)
{
	return buzzer->bzState;

}

/**
 * @brief  Buzzer_changeMelody
 *         change the melody of buzzer
 *         @note
 *
 *
 * @param  Buzzer* buzzer - the buzzer
 * @param char* name - the name of melody
 * @retval none
 */
void Buzzer_changeMelody(Buzzer* buzzer,char* name)
{
	if(!strcmp(name,"melody0")){
		_melody = 0;
	}
	else if(!strcmp(name,"melody1")){
		_melody = 1;
	}
}
/**
 * @brief  Buzzer_printMelodies
 *         print the all melodies
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void Buzzer_printMelodies()
{
	printf("The existing melodies are:\r\n");
	printf("melody0 - beep\r\n");
	printf("melody1 - little hans\r\n");

}

/**
 * @brief  Buzzer_playTask
 *         handdle the music of buzzer
 *         @note
 *
 *
 * @param void* argument - a potential argument
 * @retval none
 */
void Buzzer_playTask(void* argument)
{
	Buzzer* buzzer = (Buzzer*)argument;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	for(;;){
		if (buzzer->bzState == BUZZER_STATE_ON){
			if(_melody == 0){
				__HAL_TIM_SET_AUTORELOAD(&htim3, 100);
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 100/2);
				_countBeep++;
				if(_countBeep==20){
					buzzer->bzState = BUZZER_STATE_OFF;
					HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
					_countBeep = 0;
					_index = 0;
				}
			}
			else if(_melody == 1){
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
		}
			osDelay(1000/_lengths[_index]);
	}
}
