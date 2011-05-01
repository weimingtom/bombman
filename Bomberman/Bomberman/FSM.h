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
	Transition* GetSearchBonusTran();
	Transition* GetSearchDwallTran();
	Transition* GetFleeTran();
	Transition* GetPushBombTran();
	Transition* GetTrigBombTran();
	Transition* GetDropBombTran();
private:
	State* currentState;
	std::vector<State*> stateList;
};