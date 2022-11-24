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
#include "Rtc.h"
#include "Flash.h"
#include <iostream>
#include <fstream>
extern Dht* dht;
extern Led* redLed;
extern Buzzer* bz1;
extern Button* btn1;
extern Button* btn2;
extern Rtc* rtc;
extern SystemMonitoring* mySystem;
extern Flash* flash;

SystemMonitoring::SystemMonitoring()
{
	Threshold* threshold = (Threshold*)(flash->getAddres());
	if(threshold ->_magicNumber != 123456){
		_threshold._magicNumber = 123456;
		_threshold._warningThreshold = 26.0;
		_threshold._criticalThreshold = 27.0;
		thresholdToFlash();
	}
	else{
		_threshold._magicNumber = threshold->_magicNumber;
		_threshold._criticalThreshold = threshold->_criticalThreshold;
		_threshold._warningThreshold = threshold->_warningThreshold;

	}
	_systemStae = STATE_NORMAL;

}
void SystemMonitoring::thresholdToFlash()
{
	uint64_t* bytesThreshold = (uint64_t*)(&_threshold);
	HAL_FLASH_Unlock();
	flash->erase();
	flash->program(bytesThreshold, sizeof(_threshold));
	HAL_FLASH_Lock();
}
SystemState SystemMonitoring::getSystemState()
{
	return _systemStae;
}
void SystemMonitoring::setSystemState(SystemState systemState)
{
	_systemStae = systemState;
}
void SystemMonitoring::setWarning(double warning)
{
	printf("wr %0.2lf\r\n",_threshold._warningThreshold);
	if(warning >= _threshold._criticalThreshold){
		printf("Warning threshold need to be smaller then critical threshold\r\n");
	}
	else{
		_threshold._warningThreshold = warning;
		thresholdToFlash();
		printf("wr %0.2lf\r\n",_threshold._warningThreshold);
	}
}

void SystemMonitoring::setCritical(double critical)
{
	printf("cr %0.2lf\r\n",_threshold._criticalThreshold);
	if(critical <= _threshold._warningThreshold){
		printf("Critical threshold need to be greater then warning threshold\r\n");
	}
	else{
		_threshold._criticalThreshold = critical;
		thresholdToFlash();
	}
	printf("cr %0.2lf\r\n",_threshold._criticalThreshold);
}

double SystemMonitoring::getWarning()
{
	return _threshold._warningThreshold;
}
double SystemMonitoring::getCritical()
{
	return _threshold._criticalThreshold;
}

extern "C" void systemTask(void* argument)
{
	for(;;){
		if(dht->getTemperature()>mySystem->getCritical()){
			if(mySystem->getSystemState() == STATE_WARNING){
				mySystem->setSystemState(STATE_CRITICAL);
				bz1->start();
			}
			redLed->blink();
			if(((btn1->getState() == BUTTON_STATE_PRESS) || (btn2->getState() == BUTTON_STATE_PRESS))
					&& mySystem->getSystemState() != STATE_CRITICAL_WITHOUT_BUZZER){
				mySystem->setSystemState(STATE_CRITICAL_WITHOUT_BUZZER);
				bz1->stop();
			}
		}
		else if((dht->getTemperature()>mySystem->getWarning()) && (mySystem->getSystemState() != STATE_WARNING)){
			if(mySystem->getSystemState() == STATE_CRITICAL){
				bz1->stop();
			}
			mySystem->setSystemState(STATE_WARNING);
			redLed->on();
		}
		else if((dht->getTemperature() < mySystem->getWarning()) && (mySystem->getSystemState() != STATE_NORMAL)){
			mySystem->setSystemState(STATE_NORMAL);
			redLed->off();
		}
		osDelay(1000);
	}
}

extern "C" void saveTask(void* argument)
{
	for(;;){
		osDelay(100000);
	}
}



