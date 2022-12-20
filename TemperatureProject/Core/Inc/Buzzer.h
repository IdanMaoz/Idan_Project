/*
 * Buzzer.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

enum BuzzerState
{
	BUZZER_STATE_OFF,
	BUZZER_STATE_ON,

};

class Buzzer  {
private:
	BuzzerState _bzState;
public:
	Buzzer();
	void start();
	void stop();
};

#endif /* INC_BUZZER_H_ */
