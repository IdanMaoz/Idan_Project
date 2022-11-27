
#include "CliCommand.h"
#include "CliContainer.h"
#include "Dht.h"
#include "Rtc.h"
#include "SystemMonitoring.h"
#include <iostream>


extern SystemMonitoring* mySystem;
extern Rtc* rtc;
CliContainer container;

class setWarningCommand: public CliCommand{
	SystemMonitoring* _system;
public:
	setWarningCommand(const char* name,SystemMonitoring* system) : CliCommand(name),_system(system){}
	void doCommand(const char * param) override
	{
		_system->setWarning(atof(param));
	}

};

class setCriticalCommand: public CliCommand{
	SystemMonitoring* _system;
public:
	setCriticalCommand(const char* name,SystemMonitoring* system) : CliCommand(name),_system(system){}
	void doCommand(const char * param) override
	{
		_system->setCritical(atof(param));
	}

};

class setRtcTime: public CliCommand{
	Rtc* _rtc;
public:
	setRtcTime(const char* name,Rtc* rtc):CliCommand(name),_rtc(rtc){}
	void doCommand(const char* param) override
	{
		DateTime time;
		DateTime dateTime;
		rtc->getTime(&dateTime);
				printf("%02d:%02d:%02d-%d-%02d/%02d/%02d\r\n",
						dateTime.hours, dateTime.min, dateTime.sec,
						dateTime.weekDay,
						dateTime.day, dateTime.month, dateTime.year);
		_rtc->timeStrTok(param, &time);

	}
};
void CliCommand::CliInit()
{
	container.addCommand(new setWarningCommand("warning", mySystem));
	container.addCommand(new setCriticalCommand("critical", mySystem));
	container.addCommand(new setRtcTime("date",rtc));


}
