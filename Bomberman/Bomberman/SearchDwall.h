#pragma 
#include"State.h"

class SearchDwall : public State
{
public:
	virtual void Init(FSM* fsm);
	virtual State* Update();
};