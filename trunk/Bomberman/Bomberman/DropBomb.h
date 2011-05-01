#pragma 
#include"State.h"

class DropBomb : public State
{
public:
	virtual void Init(FSM* fsm);
	virtual State* Update();
};