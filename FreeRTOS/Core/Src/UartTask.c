/*
 * UartTask.c
 *
 *  Created on: Sep 13, 2022
 *      Author: student
 */

#include "UartTask.h"
#include "InputControl.h"

void Uart_uartTask(void *argument)
{
	for(;;){
		InputControl_HandleInput();
	}

}
