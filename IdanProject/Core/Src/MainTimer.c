/*
 * MainTimer.c
 *
 *  Created on: 26 Jul 2022
 *      Author: student
 */

#include "MainTimer.h"
#include "MyMain.h"
#include "Clock.h"
#include "main.h"
#include "Dht.h"
#include "Button.h"
#define MAX_COMMANDS 50
extern TIM_HandleTypeDef htim6;

typedef struct Command_
{

	MainTimerFunc func;
	void* object;

}Command;
static int _lenArr=0;
static Command _commandsArr[MAX_COMMANDS];

 void MainTimer_registerCallback(MainTimerFunc func,void* object)
{
	 for(int i=0;i<_lenArr;i++){
		 if(_commandsArr[i].func==func && _commandsArr[i].object==object){
			 return;
		 }
	 }
	_commandsArr[_lenArr].func=func;
	_commandsArr[_lenArr].object=object;
	_lenArr++;
}
 void MainTimer_unRegister(MainTimerFunc func,void* object)
 {
	 for(int i=0;i<_lenArr;i++){
	 	if(_commandsArr[i].func==func && _commandsArr[i].object==object){
	 		_commandsArr[i].func=_commandsArr[_lenArr-1].func;
	 		_commandsArr[i].object=_commandsArr[_lenArr-1].object;
	 		_lenArr--;
	 		return;
	 	}

	 }
 }

 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
 	if(htim==&htim6){


 		/*Led_OnTimerInterrupt(&ledB);
 		Led_OnTimerInterrupt(&ledR);

 		Buzzer_interrupt(&bz1);

 		myClock.tickCount++;
 		Button_timerInterrupt(&buttonSw1);
 		Button_timerInterrupt(&buttonSw2);
 		Dht_onTimerInterrupt(&dht);*/

 		for(int i=0;i<_lenArr;i++){
 			_commandsArr[i].func(_commandsArr[i].object);
 		}
 		myClock.tickCount++;
 	}
 }





