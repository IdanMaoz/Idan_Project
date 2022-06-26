/*
 * LedState.h
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#ifndef INC_LEDSTATE_H_
#define INC_LEDSTATE_H_

typedef enum LedState_
{
	STATE_OFF,
	STATE_FULL,
	STATE_BLINK,
	STATE_BRIGHTNESS,
	STATE_HALF,
} LED_STATE;

// Cyclically changes the flash light state to the next state
LED_STATE changeState();
LED_STATE getState();
void setState(LED_STATE newState);
#endif /* INC_LEDSTATE_H_ */
