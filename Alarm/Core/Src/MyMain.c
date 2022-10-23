/*
 * Mymain.c
 *
 *  Created on: Oct 23, 2022
 *      Author: student
 */

#include "MyMain.h"
#include "Communication.h"
#include "Cli.h"
#include "Buzzer.h"

#include <stdio.h>

Buzzer bz1;
void MyMain()
{
	Cli_init();
	Buzzer_init(&bz1);
	printf("print yess!\r\n");

}
