/*
 * Dht.cpp
 *
 *  Created on: Nov 21, 2022
 *      Author: Idan Maoz
 */

#include "Dht.h"
#include "main.h"
#include "cmsis_os.h"
#include <cstring>
#include <stdio.h>
extern osSemaphoreId_t dhtSemHandle;
extern TIM_HandleTypeDef htim16;
extern Dht* dht;
Dht::Dht(GPIO_TypeDef* gpioPort,  uint32_t gpioPin) {
	_gpioPort=gpioPort;
	_gpioPin=gpioPin;
	_bitCounter = 0;
	memset(_bytesArr,0,sizeof(_bytesArr));
	_dhtState = DHT_STATE_AWAITING_RESPONSE_START;
	_temperature = 0.0;
	_read = 0;
	_wait = 0;

}
void Dht::insertValue(){
	_temperature=(double)_bytesArr[2]+((double)_bytesArr[3])/10;

}
extern "C" int _write(int fd, char* ptr, int len);
void Dht::onGpioInterrupt(uint32_t pin)
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
			_temperature=0.0;
			insertValue();
			osSemaphoreRelease(dhtSemHandle);
			_dhtState=DHT_STATE_DATA_RECIVED;
		}
		break;
	case DHT_STATE_DATA_RECIVED:
		HAL_TIM_Base_Stop(&htim16);
		break;
	}
}

void Dht::readAsync()
{
	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.Pin = _gpioPin;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(_gpioPort, &gpioInitStruct);
	HAL_TIM_Base_Start(&htim16);
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);
	__HAL_TIM_SET_COUNTER(&htim16,0);
	memset(_bytesArr,0,sizeof(_bytesArr));
	_bitCounter = 0;
	_read = 1;
	_wait = 0;
	osSemaphoreRelease(dhtSemHandle);

}
int Dht::hasData()
{
	if(_dhtState==DHT_STATE_DATA_RECIVED){
		osSemaphoreRelease(dhtSemHandle);
		_read = 0;
		_wait = 0;
		return 1;
	}
	return 0;
}

double Dht::getTemperature()
{
	return _temperature;

}

void Dht::printTemperature()
{

	printf("The temperature is: %0.2lf\r\n",getTemperature());

}
uint8_t Dht::alreadyRead()
{
	return _read;

}
uint8_t Dht::wait()
{

	return _wait;

}


void Dht::fallingInterrupt()
{
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_SET);

	GPIO_InitTypeDef gpioInitStruct;
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	gpioInitStruct.Pin = _gpioPin;
	gpioInitStruct.Pull = GPIO_PULLUP;
	gpioInitStruct.Mode = GPIO_MODE_IT_FALLING;
	HAL_GPIO_Init(_gpioPort, &gpioInitStruct);
	_dhtState = DHT_STATE_AWAITING_RESPONSE_START;
	_wait = 1;
}

extern "C" void dhtTask(void* argument){
	for(;;){
		osSemaphoreAcquire( dhtSemHandle, osWaitForever);
		if(!dht->alreadyRead()){
			dht->readAsync();
			osDelay(19);
		}
		else if (!dht->wait()){
			dht->fallingInterrupt();
			osDelay(1);
		}
		else if(dht->hasData()){
			//dht->printTemperature();
			dht->fallingInterrupt();
			osDelay(1000);
		}
		else{
			osDelay(1);
		}
	}
}

