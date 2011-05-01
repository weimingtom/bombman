#include "FSM.h"
#include "State.h"
#include "Transition.h"
#include "SearchBonus.h"
#include "SearchDwall.h"
#include "Flee.h"
#include "PushBomb.h"
#include "TrigBomb.h"
#include "DropBomb.h"

void FSM::Update()
{
	currentState = currentState->Update();
}

void FSM::Init()
{
	stateList.push_back(new SearchBonus());
	stateList.push_back(new SearchDwall());
	stateList.push_back(new Flee());
	stateList.push_back(new PushBomb());
	stateList.push_back(new TrigBomb());
	stateList.push_back(new DropBomb());
	currentState = stateList[0];

	stateList[0]->Init(this);
	stateList[1]->Init(this);
	stateList[2]->Init(this);
	stateList[3]->Init(this);
    stateList[4]->Init(this);
	stateList[5]->Init(this);	
}

Transition* FSM::GetSearchBonusTran()
{
	return new Transition(stateList[0]);
}

Transition* FSM::GetSearchDwallTran()
{
	return new Transition(stateList[1]);
}

Transition* FSM::GetFleeTran()
{
	return new Transition(stateList[2]);
}

Transition* FSM::GetPushBombTran()
{
	return new Transition(stateList[3]);
}

Transition* FSM::GetTrigBombTran()
{
	return new Transition(stateList[4]);
}

Transition* FSM::GetDropBombTran()
{
	return new Transition(stateList[5]);
}

