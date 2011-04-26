#pragma  once
#include <vector>
#include <iostream>

class State;
class Transition;

class FSM
{
public:
	void Init();
	void Update();
	Transition* GetWaitingTransition();
	Transition* GetMovingTransition();
	Transition* GetBombingTransition();
	void WriteState();
private:
	State* currentState;
	std::vector<State*> stateList;
};