#include "FSM.h"
#include "State.h"
#include "Transition.h"

void FSM::Update()
{
	currentState = currentState->Update();
}

void FSM::WriteState()
{
	if(typeid(*currentState)==typeid(WaitingState))
		std::cout<<"waiting"<<std::endl;
	else if(typeid(*currentState)==typeid(MovingState))
		std::cout<<"moving"<<std::endl;
	else if(typeid(*currentState)==typeid(BombingState))
		std::cout<<"bombing"<<std::endl;
}

void FSM::Init()
{
	stateList.push_back(new WaitingState());
	stateList.push_back(new MovingState());
	stateList.push_back(new BombingState());
	currentState = stateList[0];

	stateList[0]->Init(this);
	stateList[1]->Init(this);
	stateList[2]->Init(this);
}

Transition* FSM::GetWaitingTransition()
{
	return new Transition(stateList[0]);
}

Transition* FSM::GetMovingTransition()
{
	return new Transition(stateList[1]);
}

Transition* FSM::GetBombingTransition()
{
	return new Transition(stateList[2]);
}

