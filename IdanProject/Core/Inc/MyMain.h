

#ifndef INC_MYMAIN_H_
#define INC_MYMAIN_H_

#include "main.h"
#include "Led.h"
#include "Buzzer.h"


void MyMain();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern Led ledB;
extern Led ledR;
extern Buzzer bz1;

#endif /* INC_MYMAIN_H_ */
