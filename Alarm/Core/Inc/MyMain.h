/*
 * Mymain.h
 *
 *  Created on: Oct 23, 2022
 *      Author: student
 */

#ifndef INC_MYMAIN_H_
#define INC_MYMAIN_H_

#include "Buzzer.h"
#include "Rtc.h"
#include "Led.h"
#include "Button.h"
void MyMain();
extern Buzzer bz1;
extern Rtc rtc1;
extern Led ledR;
extern Led ledB;
extern Button btn1;
extern Button btn2;
#endif /* INC_MYMAIN_H_ */
