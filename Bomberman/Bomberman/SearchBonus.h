#pragma 
#include"State.h"

class SearchBonus : public State
{
public:
	virtual void Init(FSM* fsm);
	virtual State* Update();
};