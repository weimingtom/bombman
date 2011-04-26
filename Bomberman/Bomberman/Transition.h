#pragma once

class State;
class Transition
{
public:
	Transition(State* next){nextState = next;}
	State* GetNextState();
	//bool IsTrue();
private:
	State* nextState;
};