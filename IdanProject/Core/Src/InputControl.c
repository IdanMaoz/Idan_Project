
#include "main.h"
#include "InputControl.h"
#include "Led.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart2;

#define MAX_BUFFER_LENGTH 100

static uint8_t _cmdbuffer[MAX_BUFFER_LENGTH];
static int _cmdcount = 0;
static int _cmdprint = 0;
static int _brightness = 0;


void InputControl_Init()
{
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

//static void update()
//{
//	switch (getState())
//	{
//	case STATE_OFF:
//		LedControl_Off();
//		break;
//
//	case STATE_FULL:
//		LedControl_Full();
//		break;
//
//	case STATE_HALF:
//		LedControl_Half();
//		break;
//
//	case STATE_BLINK:
//		LedControl_Blink();
//		break;
//
//	case STATE_BRIGHTNESS:
//		LedControl_Brightness(_brightness);
//		break;
//
//	default:
//		// do nothing
//		break;
//	}
//
//}

static int commTask()
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

static void handleCommand()
{
	char cmd[20];
	int param;

	int params = sscanf((const char*)_cmdbuffer, "%s %d", cmd, &param);

	if (params == 0)
	{
		return;
	}

	if (strcmp(cmd, "full") == 0)
	{
		setState(STATE_FULL);
	}
	else if (strcmp(cmd, "half") == 0)
	{
		setState(STATE_HALF);
	}
	else if (strcmp(cmd, "blink") == 0)
	{
		setState(STATE_BLINK);
	}
	else if (strcmp(cmd, "off") == 0)
	{
		setState(STATE_OFF);
	}
	else if (strcmp(cmd, "set") == 0 && params > 1)
	{
		_brightness = param;
		setState(STATE_BRIGHTNESS);
	}
	else
	{
		printf("Invalid command\r\n");
		return;
	}

	//update();
}


void InputControl_HandleInput()
{
	if (commTask())
	{
		handleCommand();
	}
}
