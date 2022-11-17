/*
 * Dht.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "Dht.h"
#include "main.h"
#include <cstring>
#include <stdio.h>
#include "timerContainer.h"

#define MAX_TIME_COUNTER 19

extern timerContainer timerContainer;
extern TIM_HandleTypeDef htim16;


Dht::Dht(GPIO_TypeDef* gpioPort,  uint32_t gpioPin)
{
	_gpioPort = gpioPort;
	_gpioPin = gpioPin;
	_bitCounter = 0;
	memset(_bytesArr,0,sizeof(_bytesArr));
	_dhtState = DHT_STATE_NONE;
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

void Dht::readAsync()
{
	timerContainer.add(this);
	GPIO_InitTypeDef gpioInitStruct;

	gpioInitStruct.Pin = _gpioPin;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(_gpioPort, &gpioInitStruct);

	HAL_TIM_Base_Start(&htim16);
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);
	_timeCounter=0;
	_startCount=1;
	__HAL_TIM_SET_COUNTER(&htim16,0);
}

void Dht::onGpioInterrupt()
{
	DhtState dhtState=_dhtState;
	switch(dhtState){
	case DHT_STATE_NONE:
			_dhtState=DHT_STATE_AWAITING_RESPONSE_START;
		break;
	case DHT_STATE_AWAITING_RESPONSE_START:
		_dhtState=DHT_STATE_AWAITING_RESPONSE_END;
		break;
	case DHT_STATE_AWAITING_RESPONSE_END:
		__HAL_TIM_SET_COUNTER(&htim16,0);
		_dhtState=DHT_STATE_RECEIVING_BITS;
		//memset(dht->bytesArr,0,sizeof(dht->bytesArr));
		//dht->bitCounter=0;
		break;
	case DHT_STATE_RECEIVING_BITS:
		_bytesArr[_bitCounter/8] <<= 1;
		if(__HAL_TIM_GET_COUNTER(&htim16)>=100){
			_bytesArr[_bitCounter/8] |= 1;
		}
		_bitCounter++;
		__HAL_TIM_SET_COUNTER(&htim16,0);
		if(_bitCounter==40){
			//dht->humidity=0;
			//dht->temperature=0;
			//dht->sum=0;
			insertValue();
			_dhtState=DHT_STATE_DATA_RECIVED;
		}
		break;
	case DHT_STATE_DATA_RECIVED:
		HAL_TIM_Base_Stop(&htim16);
		break;
	}

}



void Dht::timerFunc()
{

	if(_startCount==1){
		_timeCounter++;
	}
	if(_timeCounter>=MAX_TIME_COUNTER){
		HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_SET);
		_timeCounter=0;
		GPIO_InitTypeDef gpioInitStruct;
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
		gpioInitStruct.Pin = _gpioPin;
		gpioInitStruct.Pull = GPIO_PULLUP;
		gpioInitStruct.Mode = GPIO_MODE_IT_FALLING;
		HAL_GPIO_Init(_gpioPort, &gpioInitStruct);
		timerContainer.remove(this);
		_startCount=0;
		_dhtState = DHT_STATE_AWAITING_RESPONSE_START;
	}
}
int Dht::hasData()
{
	if(_dhtState==DHT_STATE_DATA_RECIVED){
		return 1;
	}
	return 0;
}
void Dht::changeStateToNone()
{
	_dhtState=DHT_STATE_NONE;
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


void Dht::printTemperature()
{
	//if(hasData()){
		printf("The temperature is: %0.2lf\r\n",getTemperature());

	//}
}



