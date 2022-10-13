/*
 * Dht.c
 *
 *  Created on: Jul 17, 2022
 *      Author: student
 */

#include "Dht.h"
#include "MainTimer.h"
#include <stdint.h>
#include <stdio.h>

extern TIM_HandleTypeDef htim16;

#define MAX_TIME_COUNTER 19

void* memset(void* s, int c, int n);
static int _startCount=0;
void Dht_init(Dht* dht,GPIO_TypeDef* gpioPort,  uint32_t gpioPin){
	dht->gpioPort=gpioPort;
	dht->gpioPin=gpioPin;
	dht->timeCounter=0;


}


static void insertValue(Dht* dht){
	dht->humidity=(double)dht->bytesArr[0]+((double)dht->bytesArr[1])/10;
	dht->temperature=(double)dht->bytesArr[2]+((double)dht->bytesArr[3])/10;
	dht->sum=(int)dht->bytesArr[4];
}


void Dht_onGpioInterrupt(Dht* dht,uint32_t pin)
{
	if(pin != dht->gpioPin)
	{
		return;
	}
	DhtState dhtState=dht->dhtState;
	switch(dhtState){
	case DHT_STATE_AWAITING_RESPONSE_START:
		dht->dhtState=DHT_STATE_AWAITING_RESPONSE_END;
		break;
	case DHT_STATE_AWAITING_RESPONSE_END:
		__HAL_TIM_SET_COUNTER(&htim16,0);
		dht->dhtState=DHT_STATE_RECEIVING_BITS;
		memset(dht->bytesArr,0,sizeof(dht->bytesArr));
		dht->bitCounter=0;
		break;
	case DHT_STATE_RECEIVING_BITS:
		dht->bytesArr[dht->bitCounter/8] <<= 1;
		if(__HAL_TIM_GET_COUNTER(&htim16)>=100){
			dht->bytesArr[dht->bitCounter/8] |= 1;
		}
		dht->bitCounter++;
		__HAL_TIM_SET_COUNTER(&htim16,0);
		if(dht->bitCounter==40){
			dht->humidity=0;
			dht->temperature=0;
			dht->sum=0;
			insertValue(dht);
			dht->dhtState=DHT_STATE_DATA_RECIVED;
		}
		break;
	case DHT_STATE_DATA_RECIVED:
		HAL_TIM_Base_Stop(&htim16);
		break;
	}

}
void Dht_onTimerInterrupt(void* obj)
{
	Dht* dht=(Dht*)obj;
	if(_startCount==1){
		dht->timeCounter++;
	}
	if(dht->timeCounter>=MAX_TIME_COUNTER){
		HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 1);
		dht->timeCounter=0;
		GPIO_InitTypeDef gpioInitStruct;
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
		gpioInitStruct.Pin = dht->gpioPin;
		gpioInitStruct.Pull = GPIO_PULLUP;
		gpioInitStruct.Mode = GPIO_MODE_IT_FALLING;
		HAL_GPIO_Init(dht->gpioPort, &gpioInitStruct);
		MainTimer_unRegister(Dht_onTimerInterrupt, dht);
		_startCount=0;
		dht->dhtState = DHT_STATE_AWAITING_RESPONSE_START;
	}
}

void Dht_readAsync(Dht* dht)
{
	MainTimer_registerCallback(Dht_onTimerInterrupt, dht);
	GPIO_InitTypeDef gpioInitStruct;

	gpioInitStruct.Pin = dht->gpioPin;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->gpioPort, &gpioInitStruct);

	HAL_TIM_Base_Start(&htim16);
	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 0);
	dht->timeCounter=0;
	_startCount=1;
	__HAL_TIM_SET_COUNTER(&htim16,0);

}

int Dht_hasData(Dht* dht)
{
	if(dht->dhtState==DHT_STATE_DATA_RECIVED){
		return 1;
	}
	return 0;
}

void Dht_changeStateToResStart(Dht* dht)
{
	dht->dhtState=DHT_STATE_AWAITING_RESPONSE_START;
}
double Dht_getTemperature(Dht* dht)
{
	return dht->temperature;

}
double Dht_getHumidity(Dht* dht)
{
	return dht->humidity;

}
int Dht_getSum(Dht* dht)
{
	return dht->sum;

}


