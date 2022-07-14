/*
 * LightSensor.c
 *
 *  Created on: Jun 28, 2022
 *      Author: student
 */

#include "LightSensor.h"

void LightSensor_init(LightSensor *ltsensor,ADC_HandleTypeDef* hadc,uint32_t max)
{
	ltsensor->hadc=hadc;
	ltsensor->max=max;
}


void LightSensor_adcInterrupt(LightSensor *ltsensor)
{
	uint32_t lt=HAL_ADC_GetValue(ltsensor->hadc);
	ltsensor->val=((ltsensor->max) * lt + (4096/2) ) /4096;

}
