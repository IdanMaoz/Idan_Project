
#include "CliContainer.h"
#include <string>

/**
 * @brief  CliContainer
 *         init the cli container
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
CliContainer::CliContainer() {
	memset(_commands, 0, sizeof(_commands));
	_counter = 0;

}

/**
 * @brief  ~CliContainer
 *         delete commands in cli container
 *         @note
 *
 *
 * @param none
 * @retval none
 */
CliContainer::~CliContainer() {
	for (int i = 0; i < _counter; i++) {
			delete _commands[i];
		}
}

/**
 * @brief  addCommand
 *         add a command to cli container
 *         @note
 *
 *
 * @param CliCommand* command - a Clicommand class
 * @retval none
 */
void CliContainer::addCommand( CliCommand* command){

	_commands[_counter] = command;
	_counter++;
}

/**
 * @brief  findCommand
 *         activate specific cli command
 *         @note
 *
 *
 * @param const char* name - the name of the command
 * @param char* param - string of the parameters
 * @retval none
 */
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
