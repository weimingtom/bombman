#pragma 
#include"State.h"

class PushBomb : public State
{
public:
	virtual void Init(FSM* fsm);
	virtual State* Update();
};