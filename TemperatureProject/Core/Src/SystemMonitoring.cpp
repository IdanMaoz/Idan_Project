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
#include "Flash.h"
#include "File.h"
#include "Rtc.h"
#include "SDCard.h"
#include <iostream>
#include <cstring>
extern Rtc* rtc;
extern Dht* dht;
extern Led* redLed;
extern Buzzer* bz1;
extern Button* btn1;
extern Button* btn2;
extern SystemMonitoring* mySystem;
extern Flash* flash;
extern File* tempFile;
extern File* eventsLogFile;
extern SDCard* sdCard;
extern osSemaphoreId dhtDataReadyHandle;
SystemMonitoring::SystemMonitoring()
{
	Threshold* threshold = (Threshold*)(flash->getAddres());
	if(threshold ->_magicNumber != 123456){
		_threshold._magicNumber = 123456;
		_threshold._warning = 26.0;
		_threshold._critical = 27.0;
		thresholdToFlash();
	}
	else{
		_threshold._magicNumber = threshold->_magicNumber;
		_threshold._critical = threshold->_critical;
		_threshold._warning = threshold->_warning;

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
	printf("wr %0.2lf\r\n",_threshold._warning);
	if(warning >= _threshold._critical){
		printf("Warning threshold need to be smaller then critical threshold\r\n");
	}
	else{
		_threshold._warning = warning;
		thresholdToFlash();
		printf("wr %0.2lf\r\n",_threshold._warning);
	}
}

void SystemMonitoring::setCritical(double critical)
{
	printf("cr %0.2lf\r\n",_threshold._critical);
	if(critical <= _threshold._warning){
		printf("Critical threshold need to be greater then warning threshold\r\n");
	}
	else{
		_threshold._critical = critical;
		thresholdToFlash();
		printf("cr %0.2lf\r\n",_threshold._critical);
	}
}

double SystemMonitoring::getWarning()
{
	return _threshold._warning;
}
double SystemMonitoring::getCritical()
{
	return _threshold._critical;
}

extern "C" void systemTask(void* argument)
{

	for(;;){
		if(dht->getTemperature()>mySystem->getCritical()){
			if(mySystem->getSystemState() == STATE_WARNING){
				mySystem->setSystemState(STATE_CRITICAL);
				bz1->start();
				char arr[100];
				DateTime dateTime;
				rtc->getTime(&dateTime);
				sprintf(arr,"%02d:%02d:%02d-%d-%02d/%02d/%02d	Critical	"
						"	The temperature increases above the critical threshold",
						dateTime.hours,dateTime.min,dateTime.sec,dateTime.weekDay,dateTime.day,
						dateTime.month, dateTime.year);
				eventsLogFile->write(arr,sizeof(arr));

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
			if(mySystem->getSystemState() == STATE_NORMAL){
				char arr[100];
				DateTime dateTime;
				rtc->getTime(&dateTime);
				sprintf(arr,"%02d:%02d:%02d-%d-%02d/%02d/%02d	Warning	"
						"	The temperature increases above the warning threshold",
						dateTime.hours,dateTime.min,dateTime.sec,dateTime.weekDay,dateTime.day,
						dateTime.month, dateTime.year);
				eventsLogFile->write(arr,sizeof(arr));
			}

			mySystem->setSystemState(STATE_WARNING);
			redLed->on();
		}
		else if((dht->getTemperature() < mySystem->getWarning()) && (mySystem->getSystemState() != STATE_NORMAL)){
			char arr[100];
			DateTime dateTime;
			rtc->getTime(&dateTime);
			sprintf(arr,"%02d:%02d:%02d-%d-%02d/%02d/%02d	Normal	"
					"	The temperature decreases the threshold",
					dateTime.hours,dateTime.min,dateTime.sec,dateTime.weekDay,dateTime.day,
					dateTime.month, dateTime.year);
			eventsLogFile->write(arr,sizeof(arr));
			mySystem->setSystemState(STATE_NORMAL);
			redLed->off();
		}
		osDelay(1000);
	}
}

extern "C" void saveTask(void* argument)
{
	for(;;){
		//osSemaphoreAcquire(dhtDataReadyHandle, osWaitForever);
		double temp = dht->getTemperature();

		if(temp>0.0){
			printf("tm %0.2lf\r\n",temp);
			char arr[100];
			DateTime dateTime;
			rtc->getTime(&dateTime);
			sprintf(arr,"%02d:%02d:%02d-%d-%02d/%02d/%02d	temp: %0.2lf",dateTime.hours,dateTime.min,
					dateTime.sec,dateTime.weekDay,dateTime.day, dateTime.month, dateTime.year,temp);
			tempFile->write(arr,sizeof(arr));
		}
		osDelay(5000);
	}
}



