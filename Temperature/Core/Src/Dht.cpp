/*
 * Dht.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "Dht.h"
#include "main.h"
#include "cmsis_os.h"
#include "MyMain.h"
#include "timerContainer.h"
#include <cstring>
#include <stdio.h>

extern Dht* dht;

#define MAX_TIME_COUNTER 19

extern timerContainer timerContainer;
extern TIM_HandleTypeDef htim16;


Dht::Dht(GPIO_TypeDef* gpioPort,  uint32_t gpioPin)
{
	_gpioPort = gpioPort;
	_gpioPin = gpioPin;
	_bitCounter = 0;
	memset(_bytesArr,0,sizeof(_bytesArr));
	_dhtState = DHT_STATE_AWAITING_RESPONSE_START;
	_humidity = 0;
	_sum = 0;
	_temperature = 0;
	_timeCounter = 0;
	_startCount = 0;
}

void Dht::insertValue(){
	_humidity=(double)_bytesArr[0]+((double)_bytesArr[1])/10;
	_temperature=(double)_bytesArr[2]+((double)_bytesArr[3])/10;
	_sum=(int)_bytesArr[4];
}

extern "C" int _write(int fd, char* ptr, int len);

void Dht::readAsync()
{
	//timerContainer.add(this);
	GPIO_InitTypeDef gpioInitStruct = {0};
	gpioInitStruct.Pin = _gpioPin;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(_gpioPort, &gpioInitStruct);
	HAL_TIM_Base_Start(&htim16);
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);
	_startCount=1;
	__HAL_TIM_SET_COUNTER(&htim16,0);

}

void Dht::onGpioInterrupt(uint16_t pin)
{
	if(pin != _gpioPin)
	{
		return;
	}
	DhtState dhtState=_dhtState;
	switch(dhtState){
		case DHT_STATE_AWAITING_RESPONSE_START:
			_dhtState=DHT_STATE_AWAITING_RESPONSE_END;
			break;
		case DHT_STATE_AWAITING_RESPONSE_END:

			__HAL_TIM_SET_COUNTER(&htim16,0);
			_dhtState=DHT_STATE_RECEIVING_BITS;
			break;
		case DHT_STATE_RECEIVING_BITS:
			_bytesArr[_bitCounter/8] <<= 1;
			if(__HAL_TIM_GET_COUNTER(&htim16)>=100){
				_bytesArr[_bitCounter/8] |= 1;
			}

			_bitCounter++;
			__HAL_TIM_SET_COUNTER(&htim16,0);
			if(_bitCounter==40){
				_humidity=0;
				_temperature=0;
				_sum=0;
				insertValue();
				_dhtState=DHT_STATE_DATA_RECIVED;
			}
			break;
		case DHT_STATE_DATA_RECIVED:
			HAL_TIM_Base_Stop(&htim16);
			break;
	}
}
/*void Dht::timerFunc()
{
	_timeCounter++;
	if(_timeCounter>=MAX_TIME_COUNTER){
		memset(_bytesArr,0,sizeof(_bytesArr));
		HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_SET);
		_timeCounter=0;
		GPIO_InitTypeDef gpioInitStruct = {0};
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
		gpioInitStruct.Pin = _gpioPin;
		gpioInitStruct.Pull = GPIO_PULLUP;
		gpioInitStruct.Mode = GPIO_MODE_IT_FALLING;

		HAL_GPIO_Init(_gpioPort, &gpioInitStruct);

		timerContainer.remove(this);
		_startCount=0;
		_dhtState = DHT_STATE_AWAITING_RESPONSE_START;
	}
}*/
int Dht::hasData()
{
	if(_dhtState==DHT_STATE_DATA_RECIVED){
		return 1;
	}
	return 0;
}
void Dht::changeStateToStart()
{
	_dhtState=DHT_STATE_AWAITING_RESPONSE_START;
}

double Dht::getTemperature()
{
	return _temperature;
}

double Dht::getHumidity()
{
	return _humidity;
}
int Dht::getSum()
{
	return _sum;
}
int Dht::getStartCount()
{
	return _startCount;
}
void Dht::printTemperature()
{

	printf("The temperature is: %0.2lf\r\n",getTemperature());

}
void Dht::setStartCount()
{
	_startCount = 0;
}
extern "C" void dhtTask(void *argument)
{
	for(;;){
		if(dht->getStartCount() == 0){
			dht->readAsync();
			osDelay(19);
		}
		else if(dht->hasData()){
			dht->printTemperature();
			dht->setStartCount();
			osDelay(980);
		}
		else{
			osDelay(1);
		}


	}
}
