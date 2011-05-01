#pragma once

class State;
class Transition
{
public:
	Transition(State* next);
	State* GetNextState();
	//bool IsTrue();
private:
	State* nextState;
};