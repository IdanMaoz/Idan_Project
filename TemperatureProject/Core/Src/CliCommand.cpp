
#include "CliCommand.h"
#include "Led.h"
#include "Communication.h"
#include "CliContainer.h"
#include "Buzzer.h"
#include "Dht.h"
#include "Rtc.h"
#include <iostream>


extern Dht* dht;
extern Rtc* rtc;
CliContainer container;

class setWarningCommand: public CliCommand{
	Dht* _dht;
public:
	setWarningCommand(const char* name,Dht* dht) : CliCommand(name),_dht(dht){}
	void doCommand(const char * param) override
	{
		_dht->setWarning(atof(param));
	}

};

class setCriticalCommand: public CliCommand{
	Dht* _dht;
public:
	setCriticalCommand(const char* name,Dht* dht) : CliCommand(name),_dht(dht){}
	void doCommand(const char * param) override
	{
		_dht->setCritical(atof(param));
	}

};

class setRtcTime: public CliCommand{
	Rtc* _rtc;
public:
	setRtcTime(const char* name,Rtc* rtc):CliCommand(name),_rtc(rtc){}
	void doCommand(const char* param) override
	{

		DateTime time;

		_rtc->timeStrTok(param, &time);

	}
};


void CliCommand::CliInit()
{
	container.addCommand(new setWarningCommand("warning", dht));
	container.addCommand(new setCriticalCommand("critical", dht));
	container.addCommand(new setRtcTime("date",rtc));


}
