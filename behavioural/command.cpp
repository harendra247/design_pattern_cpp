/*
  Command is a behavioral design pattern that turns a request into a stand-alone object that contains 
  all information about the request. This transformation lets you pass requests as a method arguments,
  delay or queue a request’s execution, and support undoable operations.
*/
#include <iostream>
#include <vector>
using namespace std;

const int MaxCommand = 5;

enum Receiver
{
	LIGHT = 0, FAN, DOOR, OVEN, NONE
}; 

// Command Interface
class Command
{
public:
	virtual void execute() = 0;
};
 
// Receiver Class
class Light 
{
public:
	void on() {
		cout << "The light is on\n";
	}
	void off() {
		cout << "The light is off\n";
	}
}; 

// Receiver Class
class Fan
{
public:
	void on() {
		cout << "The fan is on\n";
	}
	void off() {
		cout << "The fan is off\n";
	}
}; 

// Command for turning on the light
class NullCommand : public Command 
{
public:
	void execute(){ cout << "Null command: does nothing\n"; }
};

// Command for turning on the light
class LightOnCommand : public Command 
{
public:
    LightOnCommand(Light *light) : mLight(light) {}
	void execute(){
		mLight->on();
	}
private:
	Light *mLight;
};
 
// Command for turning off the light
class LightOffCommand : public Command 
{
public:
        LightOffCommand(Light *light) : mLight(light) {}
	void execute(){
		mLight->off();
	}
private:
	Light *mLight;
};

// Command for turning on the fan
class FanOnCommand : public Command 
{
public:
        FanOnCommand(Fan *fan) : mFan(fan) {}
	void execute(){
		mFan->on();
	}
private:
	Fan *mFan;
};

// Command for turning off the fan
class FanOffCommand : public Command 
{
public:
        FanOffCommand(Fan *fan) : mFan(fan) {}
	void execute(){
		mFan->off();
	}
private:
	Fan *mFan;
};

// Invoker 
// Stores the ConcreteCommand object 
class RemoteControl 
{
public:
	RemoteControl() : mOnCommand(MaxCommand), mOffCommand(MaxCommand) {
		Command *nullCmd = new NullCommand;
		for(int i = 0; i < MaxCommand; i++) {
			mOffCommand[i] = nullCmd;
			mOnCommand[i] = nullCmd;
		}
	}
	void setCommand(Receiver id, Command *onCmd, Command *offCmd) {
		mOnCommand[id] = onCmd;
		mOffCommand[id] = offCmd;
	}

	void onButtonPressed(Receiver id) {
		mOnCommand[id]->execute();
	} 

	void offButtonPressed(Receiver id) {
		mOffCommand[id]->execute();
	} 

private:
	vector<Command*> mOnCommand, mOffCommand;
};
 
// The client
int main() 
{
	// Receiver 
	Light *light = new Light;
	Fan *fan = new Fan;

	// concrete Command objects 
	LightOnCommand *lightOn = new LightOnCommand(light);
	LightOffCommand *lightOff = new LightOffCommand(light);
	FanOnCommand *fanOn = new FanOnCommand(fan);
	FanOffCommand *fanOff = new FanOffCommand(fan);
	NullCommand *nullOn = new NullCommand();
	NullCommand *nullOff = new NullCommand();

	// invoker objects
	RemoteControl *control = new RemoteControl;

	// execute
	control->setCommand(LIGHT, lightOn, lightOff);
	control->onButtonPressed(LIGHT);
	control->offButtonPressed(LIGHT);

	control->setCommand(FAN, fanOn, fanOff);
	control->onButtonPressed(FAN);
	control->offButtonPressed(FAN);

	control->setCommand(NONE, nullOn, nullOff);
	control->onButtonPressed(NONE);

	delete light, lightOn, lightOff;
	delete fan, fanOn, fanOff;
	delete control;

	return 0;
}
