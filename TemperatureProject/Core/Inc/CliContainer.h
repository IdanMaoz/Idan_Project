/*
 * CliContainer.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_CLICONTAINER_H_
#define SRC_CLICONTAINER_H_

#include "CliCommand.h"

class CliContainer {
private:
	CliCommand* _commands[20];
	int _counter;
public:
	CliContainer();
	void addCommand( CliCommand* command);
	void findCommand(const char * name, char* param);
	virtual ~CliContainer();
};

#endif /* SRC_CLICONTAINER_H_ */
