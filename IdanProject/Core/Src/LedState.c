/*
 * LedState.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#include "LedState.h"
#include "Led.h"

LedState _currentState = STATE_OFF;

LedState Led_changeState()
{
	switch (_currentState)
	{
	case STATE_OFF:
		_currentState = STATE_FULL;
		break;

	case STATE_FULL:
		_currentState = STATE_HALF;
		break;

	case STATE_HALF:
		_currentState = STATE_BLINK;
		break;

	case STATE_BLINK:
		_currentState = STATE_OFF;
		break;

	case STATE_BRIGHTNESS:
		_currentState = STATE_OFF;
		break;

	default:
		break;
	}

	return _currentState;
}

LedState  Led_getState()
{
	return _currentState;
}

void Led_setState(LedState  newState)
{
	_currentState = newState;
}
