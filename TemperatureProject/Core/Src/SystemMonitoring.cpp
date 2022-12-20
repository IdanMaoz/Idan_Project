
#include "systemMonitoring.h"
#include "cmsis_os.h"
#include "Dht.h"
#include "Led.h"
#include "main.h"
#include "Buzzer.h"
#include "Button.h"
#include "Flash.h"
#include "File.h"
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
extern osSemaphoreId dhtDataReadyHandle;

/**
 * @brief  SystemMonitoring
 *         init the system
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
SystemMonitoring::SystemMonitoring()
{
	Threshold* threshold = (Threshold*)(flash->getAddress());
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

/**
 * @brief  thresholdToFlash
 *         write the thresholds to the flash
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void SystemMonitoring::thresholdToFlash()
{
	uint64_t* bytesThreshold = (uint64_t*)(&_threshold);
	HAL_FLASH_Unlock();
	flash->erase();
	flash->program(bytesThreshold, sizeof(_threshold));
	HAL_FLASH_Lock();
}

/**
 * @brief  getSystemState
 *         get the system state
 *         @note
 *
 *
 * @param  none
 * @retval the system state
 */
SystemState SystemMonitoring::getSystemState()
{
	return _systemStae;
}

/**
 * @brief  setSystemState
 *         set the system state
 *         @note
 *
 *
 * @param  SystemState systemState - the state of system
 * @retval none
 */
void SystemMonitoring::setSystemState(SystemState systemState)
{
	_systemStae = systemState;
}

/**
 * @brief  setWarning
 *         set the warning threshold
 *         @note
 *
 *
 * @param  double warning - the warning threshold
 * @retval none
 */
void SystemMonitoring::setWarning(double warning)
{
	if(warning >= _threshold._critical){
		printf("Warning threshold need to be smaller then critical threshold\r\n");
	}
	else{
		_threshold._warning = warning;
		thresholdToFlash();
	}
}

/**
 * @brief  setCritical
 *         set the critical threshold
 *         @note
 *
 *
 * @param  double critical - the critical threshold
 * @retval none
 */
void SystemMonitoring::setCritical(double critical)
{
	if(critical <= _threshold._warning){
		printf("Critical threshold need to be greater then warning threshold\r\n");
	}
	else{
		_threshold._critical = critical;
		thresholdToFlash();
	}
}

/**
 * @brief  getWarning
 *         get the warning threshold
 *         @note
 *
 *
 * @param  none
 * @retval the warning threshold
 */
double SystemMonitoring::getWarning()
{
	return _threshold._warning;
}

/**
 * @brief  getCritical
 *         get the critical threshold
 *         @note
 *
 *
 * @param  none
 * @retval the critical threshold
 */
double SystemMonitoring::getCritical()
{
	return _threshold._critical;
}

/**
 * @brief  systemTask
 *         check every 1 second the temperature and manage the thresholds
 *         @note
 *
 *
 * @param  void* argument - a potential argument
 * @retval none
 */
extern "C" void systemTask(void* argument)
{
	char str[100];
	DateTime dateTime;
	for(;;){
		double temp = dht->getTemperature();
		if(temp > mySystem->getCritical()){
			if(mySystem->getSystemState() == STATE_WARNING || mySystem->getSystemState() == STATE_NORMAL){
				mySystem->setSystemState(STATE_CRITICAL);
				bz1->start();
				rtc->getTime(&dateTime);
				sprintf(str,"%02d:%02d:%02d-%d-%02d/%02d/%02d     Critical       temperature=%0.2lf, critical=%0.2lf",
						dateTime.hours,dateTime.min,dateTime.sec,dateTime.weekDay,dateTime.day,
						dateTime.month, dateTime.year,temp,mySystem->getCritical());

				eventsLogFile->write(str, strlen(str));

			}
			redLed->blink();
			if(((btn1->getState() == BUTTON_STATE_PRESS) || (btn2->getState() == BUTTON_STATE_PRESS))
					&& mySystem->getSystemState() != STATE_CRITICAL_WITHOUT_BUZZER){
				mySystem->setSystemState(STATE_CRITICAL_WITHOUT_BUZZER);
				bz1->stop();
			}
		}
		else if((temp > mySystem->getWarning()) && (mySystem->getSystemState() != STATE_WARNING)){
			if(mySystem->getSystemState() == STATE_CRITICAL){
				bz1->stop();
			}
			if(mySystem->getSystemState() == STATE_NORMAL){
				rtc->getTime(&dateTime);
				sprintf(str,"%02d:%02d:%02d-%d-%02d/%02d/%02d     Warning        temperature=%0.2lf, warning=%0.2lf",
						dateTime.hours,dateTime.min,dateTime.sec,dateTime.weekDay,dateTime.day,
						dateTime.month, dateTime.year,temp,mySystem->getWarning());
				eventsLogFile->write(str, strlen(str));
			}

			mySystem->setSystemState(STATE_WARNING);
			redLed->on();
		}
		else if((temp < mySystem->getWarning()) && (mySystem->getSystemState() != STATE_NORMAL)){
			rtc->getTime(&dateTime);
			sprintf(str,"%02d:%02d:%02d-%d-%02d/%02d/%02d     Normal         temperature=%0.2lf, warning=%0.2lf",
					dateTime.hours,dateTime.min,dateTime.sec,dateTime.weekDay,dateTime.day,
					dateTime.month, dateTime.year,temp,mySystem->getWarning());
			eventsLogFile->write(str, strlen(str));
			mySystem->setSystemState(STATE_NORMAL);
			redLed->off();
		}
		osDelay(1000);
	}
}

/**
 * @brief  saveTask
 *         save every 1 minutes the temperature into temp file
 *         @note
 *
 *
 * @param  void* argument - a potential argument
 * @retval none
 */
extern "C" void saveTask(void* argument)
{
	osSemaphoreAcquire(dhtDataReadyHandle, osWaitForever);
	char arr[100];
	DateTime dateTime;
	for(;;){
		osSemaphoreAcquire(dhtDataReadyHandle, osWaitForever);
		double temp = dht->getTemperature();
		rtc->getTime(&dateTime);
		sprintf(arr,"%02d:%02d:%02d-%d-%02d/%02d/%02d	temperature=%0.2lf",dateTime.hours,dateTime.min,
				dateTime.sec,dateTime.weekDay,dateTime.day, dateTime.month, dateTime.year,temp);
		tempFile->write(arr,strlen(arr));
		osDelay(60000);
	}
}
