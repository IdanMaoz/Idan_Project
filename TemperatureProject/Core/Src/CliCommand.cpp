
#include "CliCommand.h"
#include "Led.h"
#include "Communication.h"
#include "CliContainer.h"
#include "Buzzer.h"
#include "Dht.h"
#include <iostream>


extern Dht* dht;
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

class printTemperatureCommand: public CliCommand{
	Dht* _dht;
public:
	printTemperatureCommand(const char* name,Dht* dht) : CliCommand(name),_dht(dht){}
	void doCommand(const char * param) override
	{
		_dht->printTemperature();
	}

};


void CliCommand::CliInit()
{
	container.addCommand(new setWarningCommand("warning", dht));
	container.addCommand(new setCriticalCommand("critical", dht));
	//container.addCommand(new printTemperatureCommand("print",dht));

}
