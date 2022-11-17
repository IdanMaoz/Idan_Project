/*
 * CliContainer.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "CliContainer.h"
#include <string>
CliContainer::CliContainer() {
	memset(_commands, 0, sizeof(_commands));
	_counter = 0;

}

CliContainer::~CliContainer() {
	for (int i = 0; i < _counter; i++) {
			delete _commands[i];
		}
}
void CliContainer::addCommand( CliCommand* command){

	_commands[_counter] = command;
	_counter++;
}
void CliContainer::findCommand(const char * name, char* param)
{
	for(int i=0;i<_counter;i++){
		if(strcmp(name,_commands[i]->getName()) == 0){
			_commands[i]->doCommand(param);
			return;
		}

	}
	printf("Invalid command\r\n");

}
