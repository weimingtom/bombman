#pragma 
#include"State.h"

class TrigBomb: public State
{
public:
	virtual void Init(FSM* fsm);
	virtual State* Update();
};