#pragma once
#include<vector>

class FSM;
class Transition;
class State
{
public:
	virtual void Init(FSM* fsm);
	virtual State* Update(){return NULL;}
protected:
	std::vector<Transition*> transitionList;
};

