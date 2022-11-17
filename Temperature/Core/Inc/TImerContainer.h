/*
 * TImerContainer.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_TIMERCONTAINER_H_
#define SRC_TIMERCONTAINER_H_

#include "TimerTask.h"
class timerContainer {
private:
	TimerTask* _timerTasks[10];
	int _counter;
public:
	timerContainer();
	void add(TimerTask* timerTask);
	void remove(TimerTask* timerTask);
	void timeInterrupt();
};


#endif /* SRC_TIMERCONTAINER_H_ */
