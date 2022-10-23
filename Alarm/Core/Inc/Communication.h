/*
 * commTask.h
 *
 *  Created on: 10 Jul 2022
 *      Author: student
 */

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_

typedef void (*HandlerFunc)(void*, char *);


void Communication_register(char* commandName, HandlerFunc func, void* object);



#endif /* INC_COMMUNICATION_H_ */
