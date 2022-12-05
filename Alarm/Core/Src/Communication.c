/*
 * commTask.c
 *
 *  Created on: 10 Jul 2022
 *      Author: student
 */


#include "Communication.h"

#include "main.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;

#define MAX_BUFFER_LENGTH 100
#define MAX_COMMANDS 20

static uint8_t _cmdbuffer[MAX_BUFFER_LENGTH];
static int _cmdcount = 0;
static int _cmdprint = 0;



typedef struct Command_
{
	char commandName[20];
	HandlerFunc func;
	void* object;

}Command;

static Command _commandsArr[MAX_COMMANDS];

static int _CommandArrLen=0;


/**
 * @brief  task
 *         recieve the data
 *         @note
 *
 *
 * @param  none
 * @retval 0 if the char isn't /n or /r, 1 if it is
 */
 int task()
{
	uint8_t ch;

	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 10);
	if (Status != HAL_OK)
	{
		if ((huart2.Instance->ISR & USART_ISR_ORE) != 0)
		{
			__HAL_UART_CLEAR_OREFLAG(&huart2);
		}

		// here we have a time to print the command
		while (_cmdprint < _cmdcount)
		{
			HAL_UART_Transmit(&huart2, &_cmdbuffer[_cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch == '\r' || ch == '\n')
	{
		// here we have a time to print the command
		while (_cmdprint < _cmdcount)
		{
			HAL_UART_Transmit(&huart2, &_cmdbuffer[_cmdprint++], 1, 0xFFFF);
		}

		HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);

		_cmdbuffer[_cmdcount] = 0;
		_cmdcount = 0;
		_cmdprint = 0;

		// command is ready
		return 1;
	}
	else if (ch == '\b')
	{
		char bs[] = "\b \b";
		_cmdcount--;
		_cmdprint--;
		HAL_UART_Transmit(&huart2, (uint8_t*)bs, strlen(bs), 0xFFFF);
	}
	else
	{
		if (_cmdcount >= MAX_BUFFER_LENGTH)
		{
			_cmdcount = 0;
			_cmdprint = 0;
		}

		_cmdbuffer[_cmdcount++] = ch;
	}

	return 0;
}

 /**
  * @brief  handle
  *         handle the data
  *         @note
  *
  *
  * @param  none
  * @retval none
  */
 void handle()
{
	char cmd[20];
	char name[20];
	char param[20];

	int params = sscanf((const char*)_cmdbuffer, "%s %s %s", cmd, name,param);

	if (params == 0)
	{
		return;
	}
	for(int i=0;i<_CommandArrLen;i++){
		if(strcmp(cmd,_commandsArr[i].commandName) == 0){
			_commandsArr[i].func(_commandsArr[i].object, name,param);
			return;
		}

	}
	printf("Invalid command\r\n");

}

 /**
   * @brief  Communication_handleTask
   *         check if the data is ready
   *         @note
   *
   *
   * @param  void* argument - a potential argument
   * @retval none
   */
void Communication_handleTask(void *argument)
{
	for(;;){
		if(task()){
			handle();
		}
	}
}
/**
  * @brief  Communication_register
  *         add to commands array  the command
  *         @note
  *
  *
  * @param  char* commandName - the command name
  * @param HandlerFunc func - the function that the command used
  * @param void* object - the object of the command
  * @retval none
  */
void Communication_register(char* commandName, HandlerFunc func,void* object)
{

	strncpy(_commandsArr[_CommandArrLen].commandName, commandName, 20);
	_commandsArr[_CommandArrLen].func=func;
	_commandsArr[_CommandArrLen].object=object;
	_CommandArrLen++;
}
