

#ifndef INC_DHT_H_
#define INC_DHT_H_
#include "main.h"

typedef enum DhtState_
{
	DHT_STATE_AWAITING_RESPONSE_START,
	DHT_STATE_AWAITING_RESPONSE_END,
	DHT_STATE_RECEIVING_BITS,
	DHT_STATE_DATA_RECIVED

}DhtState;

typedef struct Dht_
{
	GPIO_TypeDef* gpioPort;
	uint32_t gpioPin;
	double temperature;
	double humidity;
	int sum;
	DhtState dhtState;
	uint8_t bytesArr[5];
	uint8_t bitCounter;
	uint8_t timeCounter;

} Dht;



void Dht_init(Dht* dht,GPIO_TypeDef* gpioPort,  uint32_t gpioPin);

void Dht_readAsync(Dht* dht);
void Dht_onGpioInterrupt(Dht* dht,uint32_t pin);
void Dht_onTimerInterrupt(void* obj);
int Dht_hasData(Dht* dht);
void Dht_changeStateToResStart(Dht* dht);

#endif /* INC_DHT_H_ */
