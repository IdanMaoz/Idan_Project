/*
 * CLI.c
 *
 *  Created on: 12 Jul 2022
 *      Author: student
 */

#include "Communication.h"
#include "CLI.h"
#include "MyMain.h"
#include "Led.h"
#include "Button.h"
#include "Buzzer.h"

#include <stdlib.h>

static void cmdLedOn(void* obj, char* params)
{
	(void)params;
	Led* led = (Led*)obj;
	Led_On(led);

}
static void cmdLedOff(void* obj, char* params)
{
	(void)params;
	Led* led = (Led*)obj;
	Led_Off(led);
}

static void cmdLedBlink(void* obj, char* params)
{
	Led* led = (Led*)obj;
	Led_Blink(led, atoi(params));
}
static void cmdLedBrightness(void* obj, char* params)
{
	Led* led = (Led*)obj;
	Led_Brightness(led, atoi(params));
}

static void cmdBuzzerStart(void* obj, char* params)
{

	Buzzer_start();

}
static void cmdBuzzerStop(void* obj, char* params)
{
	Buzzer_stop();
}


void Cli_init(){
	Communication_register("blueOn", &cmdLedOn, &ledB);
	Communication_register("blueOff", &cmdLedOff, &ledB);
	Communication_register("blueBlink", &cmdLedBlink, &ledB);
	Communication_register("blueBrightness", &cmdLedBrightness, &ledB);

	Communication_register("redOn", &cmdLedOn, &ledR);
	Communication_register("redOff", &cmdLedOff, &ledR);
	Communication_register("redBlink", &cmdLedBlink, &ledR);
	Communication_register("redBrightness", &cmdLedBrightness, &ledR);
	Communication_register("buzzerStart", &cmdBuzzerStart, &bz1);
	Communication_register("buzzerStop", &cmdBuzzerStop, &bz1);
}
