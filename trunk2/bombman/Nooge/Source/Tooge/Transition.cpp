#include"Transition.h"


///////////////////////////////////////////////////////transition///////////////////////////////////////////////////
Transition::Transition(NPCController* ctrl, State* nextState):
mNextState(nextState)
{
	mCtrl = ctrl;
}

State* Transition::GetNextState()
{
	return mNextState;
}

//////////////////////////////////////////////////ToSilly/////////////////////////////////////////////
ToSilly::ToSilly(NPCController* ctrl,State* next):
Transition(ctrl,next)
{}

bool ToSilly::IsTrue()
{
	return true;
}
//////////////////////////////////////////////////ToFlee///////////////////////////////////////////////

ToFlee::ToFlee(NPCController* ctrl,State* next):
Transition(ctrl,next)
{}

bool ToFlee::IsTrue()
{
	
	int row = mCtrl->GetCharacter()->GetBoundingBox().Row();
	int col = mCtrl->GetCharacter()->GetBoundingBox().Col();
	float speed = mCtrl->GetCharacter()->GetSpeed();
	if(mCtrl->GetDangerGrid()->GetValue(col,row)<=3.0)//Grid::SideLen/2/speed
		return true;
	return false;
}

////////////////////////////////////////////////ToSearchBonus////////////////////////////////////

ToSearchBonus::ToSearchBonus(NPCController* ctrl,State* next):
Transition(ctrl,next)
{}

bool ToSearchBonus::IsTrue()
{
	Pos NearestBonus = mCtrl->NearestBonusPos();
	if(NearestBonus == Pos(-1,-1) )//|| rand()%10<5
		return false;
		return true;
}