/*
 * LightSensor.h
 *
 *  Created on: Jun 28, 2022
 *      Author: student
 */

#ifndef INC_LIGHTSENSOR_H_
#define INC_LIGHTSENSOR_H_


#include <stdint.h>
#include "main.h"

typedef struct LightSensor_
{
	ADC_HandleTypeDef* hadc;
	uint32_t max;
	uint32_t val;


}LightSensor;

void LightSensor_init(LightSensor *ltsensor,ADC_HandleTypeDef* hadc,uint32_t max);
void LightSensor_adcInterrupt(LightSensor *ltsensor);
#endif /* INC_LIGHTSENSOR_H_ */
