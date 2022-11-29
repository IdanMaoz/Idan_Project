
#include "CliCommand.h"
#include "CliContainer.h"
#include "Dht.h"
#include "Rtc.h"
#include "File.h"
#include "SystemMonitoring.h"
#include <iostream>


extern SystemMonitoring* mySystem;
extern Rtc* rtc;
extern File* eventsLogFile;
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
class printLogFile: public CliCommand{
	File* _file;
public:
	printLogFile(const char* name,File* file) : CliCommand(name),_file(file){}
	void doCommand(const char * param) override
	{
		_file->read();
	}

};
class clearLogFile: public CliCommand{
	File* _file;
public:
	clearLogFile(const char* name,File* file) : CliCommand(name),_file(file){}
	void doCommand(const char * param) override
	{
		_file->clear();
	}

};


void CliCommand::CliInit()
{
	container.addCommand(new setWarningCommand("warning", mySystem));
	container.addCommand(new setCriticalCommand("critical", mySystem));
	container.addCommand(new setRtcTime("date",rtc));
	container.addCommand(new printLogFile("print",eventsLogFile));
	container.addCommand(new clearLogFile("clear",eventsLogFile));


}
