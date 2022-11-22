/*
 * systemMonitoring.h
 *
 *  Created on: 22 Nov 2022
 *      Author: student
 */

#ifndef INC_SYSTEMMONITORING_H_
#define INC_SYSTEMMONITORING_H_

typedef enum SystemState_
{
	STATE_NORMAL,
	STATE_WARNING,
	STATE_CRITICAL,
	STATE_CRITICAL_WITHOUT_BUZZER
}SystemState;
class SystemMonitoring{
private:
	SystemState _systemStae;
public:
	SystemMonitoring();
	SystemState getSystemState();
	void setSystemState(SystemState systemState);
};



#endif /* INC_SYSTEMMONITORING_H_ */
