/*
 * Communication.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_COMMUNICATION_H_
#define SRC_COMMUNICATION_H_

#define MAX_BUFFER_LENGTH 100

class Communication{
private:
	uint8_t _cmdbuffer[MAX_BUFFER_LENGTH];
	int _cmdcount;
	int _cmdprint;
public:
	Communication();
	int task();
	void handle();
};

#endif /* SRC_COMMUNICATION_H_ */
