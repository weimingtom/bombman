#include "Transition.h"
#include "State.h"

State* Transition::GetNextState()
{
	return nextState;
}

Transition::Transition( State* next )
{
	nextState = next;
}
