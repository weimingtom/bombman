#include "State.h"
#include "FSM.h"
#include "Transition.h"

void WaitingState::Init(FSM* fsm)
{
	transitionList.push_back(fsm->GetMovingTransition());
	transitionList.push_back(fsm->GetBombingTransition());
}

State* WaitingState::Update()
{
	return transitionList[0]->GetNextState();
}

void MovingState::Init(FSM* fsm)
{
	transitionList.push_back(fsm->GetWaitingTransition());
	transitionList.push_back(fsm->GetBombingTransition());
}

State* MovingState::Update()
{
	return transitionList[1]->GetNextState();
}

void BombingState::Init(FSM* fsm)
{
	transitionList.push_back(fsm->GetWaitingTransition());
	transitionList.push_back(fsm->GetMovingTransition());
}

State* BombingState::Update()
{
	return transitionList[0]->GetNextState();
}

void State::Init(FSM* fsm) {

}