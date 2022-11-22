/*
 * systemMonitoring.cpp
 *
 *  Created on: 22 Nov 2022
 *      Author: student
 */

#include "systemMonitoring.h"
#include "cmsis_os.h"
#include "Dht.h"
#include "Led.h"
#include "main.h"
#include "Buzzer.h"
#include "Button.h"
extern Dht* dht;
extern Led* redLed;
extern Buzzer* bz1;
extern Button* btn1;
extern Button* btn2;
extern SystemMonitoring* mySystem;
SystemMonitoring::SystemMonitoring()
{
	_systemStae = STATE_NORMAL;
}
SystemState SystemMonitoring::getSystemState()
{
	return _systemStae;
}
void SystemMonitoring::setSystemState(SystemState systemState)
{
	_systemStae = systemState;
}
extern "C" void systemTask(void* argument)
{
	for(;;){
		if(dht->getTemperature()>dht->getCritical()){
			if(mySystem->getSystemState() == STATE_WARNING){
				mySystem->setSystemState(STATE_CRITICAL);
				bz1->start();
			}
			redLed->blink();
			if((btn1->getState() == BUTTON_STATE_PRESS) || (btn2->getState() == BUTTON_STATE_PRESS)){
				mySystem->setSystemState(STATE_CRITICAL_WITHOUT_BUZZER);
				bz1->stop();
			}
		}
		else if(dht->getTemperature()>dht->getWarning()){

			mySystem->setSystemState(STATE_WARNING);
			redLed->on();
			bz1->stop();
		}
		else{
			mySystem->setSystemState(STATE_NORMAL);
			redLed->off();
		}
		osDelay(1000);
	}
}



