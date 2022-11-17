
#include "CliCommand.h"
#include "Led.h"
#include "Communication.h"
#include "CliContainer.h"
#include "Buzzer.h"
#include "Dht.h"
#include <iostream>


extern Buzzer bz1;
CliContainer container;
extern Led* redLed;
extern Led* blueLed;
extern Dht* dht;
class ledOnCommand: public CliCommand{
	Led* _led;
public:
	ledOnCommand(const char* name,Led* led) : CliCommand(name),_led(led){}
	void doCommand(const char * param) override
	{
		_led->on();
	}

};

class ledOffCommand: public CliCommand{
	Led* _led;
public:
	ledOffCommand(const char* name,Led* led) : CliCommand(name),_led(led){}
	void doCommand(const char * param) override
	{
		_led->off();
	}

};

class ledBlinkCommand: public CliCommand{
	Led* _led;

public:
	ledBlinkCommand(const char* name, Led* led) : CliCommand(name), _led(led){}
	void doCommand(const char * param) override
	{
		_led->blink(atoi(param));
	}

};


class buzzerStartCommand: public CliCommand{
	Buzzer* _buzzer;

public:
	buzzerStartCommand(const char* name, Buzzer* buzzer): CliCommand(name),_buzzer(buzzer){}
	void doCommand(const char * param) override
	{
		_buzzer->start();
	}
};

class buzzerStopCommand: public CliCommand{
	Buzzer* _buzzer;

public:
	buzzerStopCommand(const char* name, Buzzer* buzzer): CliCommand(name),_buzzer(buzzer){}
	void doCommand(const char * param) override
	{
		_buzzer->stop();

	}
};

class dhtPrintCommand: public CliCommand{
	Dht* _dht;

public:
	dhtPrintCommand(const char* name, Dht* dht): CliCommand(name),_dht(dht){}
	void doCommand(const char * param) override
	{
		_dht->printTemperature();
	}
};
void CliCommand::CliInit()
{
	container.addCommand(new ledOnCommand("blueOn", blueLed));
	container.addCommand(new ledOnCommand("redOn", redLed));
	container.addCommand(new ledOffCommand("blueOff", blueLed));
	container.addCommand(new ledOffCommand("redOff",redLed));
	container.addCommand(new ledBlinkCommand("blueBlink", blueLed));
	container.addCommand(new ledBlinkCommand("redBlink", redLed));
	container.addCommand(new buzzerStartCommand("buzzerStart",&bz1));
	container.addCommand(new buzzerStopCommand("buzzerStop",&bz1));
	container.addCommand(new dhtPrintCommand("dhtPrint",dht));

}
