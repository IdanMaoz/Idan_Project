/*
 * Communication.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_COMMUNICATION_H_
#define SRC_COMMUNICATION_H_

typedef void (*HandlerFunc)(char *);

int Communication_task();
void Communication_handle();




#endif /* SRC_COMMUNICATION_H_ */
