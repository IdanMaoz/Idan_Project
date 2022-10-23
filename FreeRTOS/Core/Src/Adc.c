/*
 * Adc.c
 *
 *  Created on: Sep 15, 2022
 *      Author: student
 */

#include "Adc.h"
#include "main.h"
#include "cmsis_os.h"
uint32_t ltsensor;
extern  ADC_HandleTypeDef hadc1;
void Adc_readTask(void * argument)
{
	for(;;){
		HAL_ADC_Start(&hadc1);
		ltsensor=HAL_ADC_GetValue(&hadc1);
		osDelay(1000);
	}
}
