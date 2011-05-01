#pragma 
#include"State.h"

class Flee : public State
{
public:
	virtual void Init(FSM* fsm);
	virtual State* Update();
};