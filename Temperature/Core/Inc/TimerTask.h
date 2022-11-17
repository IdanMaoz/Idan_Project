/*
 * TimerTask.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_TIMERTASK_H_
#define SRC_TIMERTASK_H_

class TimerTask {
public:
	virtual ~TimerTask(){};
	virtual void timerFunc() = 0;

};


#endif /* SRC_TIMERTASK_H_ */
