
#include "CliCommand.h"
#include "CliContainer.h"
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
		if(isdigit(param[0])){
			_system->setWarning(atof(param));
		}
		else{
			printf("Warning param isn't number\r\n");
		}
	}
};

class setCriticalCommand: public CliCommand{
	SystemMonitoring* _system;
public:
	setCriticalCommand(const char* name,SystemMonitoring* system) : CliCommand(name),_system(system){}
	void doCommand(const char * param) override
	{
		if(isdigit(param[0])){
			_system->setCritical(atof(param));
		}
		else{
			printf("Critical param isn't number\r\n");
		}
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

/**
 * @brief  CliInit
 *         init the cliCommand
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void CliCommand::CliInit()
{
	container.addCommand(new setWarningCommand("warning", mySystem));
	container.addCommand(new setCriticalCommand("critical", mySystem));
	container.addCommand(new setRtcTime("date",rtc));
	container.addCommand(new printLogFile("print",eventsLogFile));
	container.addCommand(new clearLogFile("clear",eventsLogFile));
}
