/*
 * Dht.h
 *
 *  Created on: Nov 21, 2022
 *      Author: Idan Maoz
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_

#include "main.h"

enum DhtState
{
	DHT_STATE_AWAITING_RESPONSE_START,
	DHT_STATE_AWAITING_RESPONSE_END,
	DHT_STATE_RECEIVING_BITS,
	DHT_STATE_DATA_RECIVED

};

class Dht {
private:
	GPIO_TypeDef* _gpioPort;
	uint32_t _gpioPin;
	double _temperature;
	DhtState _dhtState;
	uint8_t _bytesArr[5];
	uint8_t _bitCounter;
	uint8_t _read;
	uint8_t _wait;
public:
	Dht(GPIO_TypeDef* gpioPort,  uint32_t gpioPin);
	void readAsync();
	void onGpioInterrupt(uint32_t pin);
	void pullUp();
	int hasData();
	uint8_t alreadyRead();
	uint8_t wait();
	double getTemperature();
private:
	void insertValue();
};

#endif /* INC_DHT_H_ */
