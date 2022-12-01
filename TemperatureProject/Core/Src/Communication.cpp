/*
 * Communication.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */
#include "main.h"
#include "Communication.h"
#include "CliContainer.h"
#include "cmsis_os.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
extern UART_HandleTypeDef huart2;
extern CliContainer container;
extern Communication* com;
#define MAX_BUFFER_LENGTH 100
#define MAX_COMMANDS 20

/**
 * @brief  Communication
 *         init the communication
 *         @note
 *
 *
 * @param  none
 */
Communication::Communication()
{
	memset(_cmdbuffer,0,sizeof(_cmdbuffer));
	_cmdcount = 0;
	_cmdprint = 0;
}

/**
 * @brief  task
 *         recieve the data
 *         @note
 *
 *
 * @param  none
 * @retval 0 if the char isn't /n or /r, 1 if it is
 */
 int Communication::task()
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
 void Communication::handle()
{
	char cmd[20];
	char param[20];

	int params = sscanf((const char*)_cmdbuffer, "%s %s", cmd, param);

	if (params == 0)
	{
		return;
	}
	container.findCommand(cmd, param);
}

 /**
  * @brief  comTask
  *         check if the data is ready
  *         @note
  *
  *
  * @param  void* argument - a potential argument
  * @retval none
  */
 extern "C" void comTask(void* argument)
 {
	 for(;;){
		 if(com->task()){
			 com->handle();
		 }
		 osDelay(10);
	 }
 }

