/*
 * LedState.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#include "LedState.h"
#include "Led.h"

LED_STATE _currentState = STATE_OFF;

LED_STATE changeState()
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

LED_STATE  getState()
{
	return _currentState;
}

void setState(LED_STATE  newState)
{
	_currentState = newState;
}
