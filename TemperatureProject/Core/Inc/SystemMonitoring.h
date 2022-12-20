/*
 * systemMonitoring.h
 *
 *  Created on: 22 Nov 2022
 *      Author: student
 */

#ifndef INC_SYSTEMMONITORING_H_
#define INC_SYSTEMMONITORING_H_
#include "stdint.h"
#include "Rtc.h"
typedef enum SystemState_
{
	STATE_NORMAL,
	STATE_WARNING,
	STATE_CRITICAL,
	STATE_CRITICAL_WITHOUT_BUZZER
}SystemState;

typedef struct Threshold_
{
	uint32_t _magicNumber;
	double _warning;
	double _critical;
}Threshold;

class SystemMonitoring{
private:
	SystemState _systemStae;
	Threshold _threshold;
public:
	SystemMonitoring();
	SystemState getSystemState();
	void setSystemState(SystemState systemState);
	void setCritical(double critical);
	void setWarning(double warning);
	double getWarning();
	double getCritical();
private:
	void thresholdToFlash();
};



#endif /* INC_SYSTEMMONITORING_H_ */
