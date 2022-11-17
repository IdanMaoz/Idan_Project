/*
 * Dht.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_DHT_H_
#define SRC_DHT_H_
#include "main.h"
#include "TimerTask.h"
typedef enum DhtState_
{
	DHT_STATE_NONE,
	DHT_STATE_AWAITING_RESPONSE_START,
	DHT_STATE_AWAITING_RESPONSE_END,
	DHT_STATE_RECEIVING_BITS,
	DHT_STATE_DATA_RECIVED

}DhtState;

class Dht : public TimerTask{
private:
	GPIO_TypeDef* _gpioPort;
	uint32_t _gpioPin;
	double _temperature;
	double _humidity;
	int _sum;
	DhtState _dhtState;
	uint8_t _bytesArr[5];
	uint8_t _bitCounter;
	uint8_t _timeCounter;
	uint8_t _startCount;

public:
	Dht(GPIO_TypeDef* gpioPort,  uint32_t gpioPin);
	void readAsync();
	void onGpioInterrupt();
	int hasData();
	void changeStateToNone();
	double getTemperature();
	double getHumidity();
	int getSum();
	virtual void timerFunc() override;
	void printTemperature();
private:
	void insertValue();
};

#endif /* SRC_DHT_H_ */
