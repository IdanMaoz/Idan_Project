/*
 * MainTimer.h
 *
 *  Created on: 26 Jul 2022
 *      Author: student
 */

#ifndef INC_MAINTIMER_H_
#define INC_MAINTIMER_H_

typedef void (*MainTimerFunc)(void*);
void MainTimer_registerCallback(MainTimerFunc func,void* object);
void MainTimer_unRegister(MainTimerFunc func,void* object);

#endif /* INC_MAINTIMER_H_ */
