/*
 * CliCommand.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_CLICOMMAND_H_
#define SRC_CLICOMMAND_H_

#include<string.h>

class CliCommand {
private:
	char _name[20];
public:
	CliCommand(const char * name) {
		strcpy(this->_name, name);
	}
	const char * getName() const { return _name; }
	virtual ~CliCommand(){};
	virtual void doCommand(const char* param) = 0;
	static void CliInit();
};

#endif /* SRC_CLICOMMAND_H_ */
