#include"State.h"
#include<algorithm>
#include "WinFrame.h"
#include"App.h"

///////////////////////////////State/////////////////////////////////
State* State::Update(float dt)
{
	vector<Transition*>::iterator it = mTransitionList.begin();
	vector<Transition*>::iterator end = mTransitionList.end();

	for (; it !=end ; ++it)
		if ((*it)->IsTrue())
		{
			if(this != (*it)->GetNextState() )//&& this->mTimer->IsOpen() && this->mTimer->End()>=1.0
			{
				SetTimer(false);
				(*it)->GetNextState()->SetTimer(true);
			}
			return (*it) ->GetNextState();
		}
	return this;
}

void State::SetTimer(bool open)
{
	mTimer->Begin();
	mTimer->SetOpen(true);
}

double State::GetTimer()
{
	if(!mTimer->IsOpen())
		return 0;
	return mTimer->End();
}

void State::AddTransition(Transition* transition)
{
	mTransitionList.push_back(transition);
}

State::State(NPCController* ctrl)
{
	mCtrl = ctrl;
	mTimer = Ref<Timer>(new Timer);
}

////////////////////////////////SillyState////////////////////////////////
SillyState::SillyState(NPCController* ctrl):
State(ctrl)
{}

int SillyState::GetAction()
{
	return IDLE;
}

////////////////////////////////FleeState///////////////////////////////

FleeState::FleeState(NPCController* ctrl):
State(ctrl)
{}

int FleeState::GetAction()
{
	static int dirX[4] = { -1, 0, 1,  0};
	static int dirY[4] = {  0, 1, 0, -1};
	//std::vector<Pos> safe;
	Pos myPosition;
	Pos safe;

	myPosition = Pos(mCtrl->GetCharacter()->GetBoundingBox().Col(),mCtrl->GetCharacter()->GetBoundingBox().Row());
	//safe.push_back(myPosition);
	safe = myPosition;

	AIMap* dangerGrid = mCtrl->GetDangerGrid();

	//find safer place
	for(int i = 0;i<4;++i)
	{
		float safeValue = dangerGrid->GetValue(myPosition.col+dirX[i],myPosition.row+dirY[i]);
		if(safeValue!=-DWALL && safeValue!=-UWALL )
		{
			if(safeValue > dangerGrid->GetValue(safe))
			{
				//safe.clear();
				//safe.push_back(Pos(myPosition.col+dirX[i],myPosition.row+dirY[i]));
				safe = Pos(myPosition.col+dirX[i],myPosition.row+dirY[i]);
			}
			else if(safeValue == dangerGrid->GetValue(safe))
			{
				//safe.push_back(Pos(myPosition.col+dirX[i],myPosition.row+dirY[i]));
				safe = Pos(Pos(myPosition.col+dirX[i],myPosition.row+dirY[i]));
			}
		}
	}

	//choose action
	//flee time too long! waiting for death!
	if(mTimer->End()>1.0)
	{ 
		return IDLE;
	}

	//int t = rand()%safe.size();
	if(safe.row == myPosition.row+dirY[0] && safe.col== myPosition.col+dirX[0]  )//can NPC pass the next ����
	{
		return MOVE_LEFT;
	}
	else if(safe.row == myPosition.row+dirY[1] && safe.col== myPosition.col+dirX[1] )
	{
		return MOVE_DOWN;
	}
	else if(safe.row == myPosition.row+dirY[2] && safe.col== myPosition.col+dirX[2] )
	{
		return MOVE_RIGHT;
	}
	else if(safe.row == myPosition.row+dirY[3] && safe.col== myPosition.col+dirX[3])
	{
		//LogTrace(" UP\n");
		return MOVE_UP;
	}
	else
	{
		//LogTrace(" IDLE\n");
		return IDLE;
	}

}

///////////////////////////////SearchBonusState////////////////////
SearchBonusState::SearchBonusState(NPCController* ctrl):
State(ctrl)
{}

int SearchBonusState::GetAction()
{
	Pos myPosition = Pos(mCtrl->GetCharacter()->GetBoundingBox().Col(),mCtrl->GetCharacter()->GetBoundingBox().Row());
	Pos nearestBonus = mCtrl->NearestBonusPos();
	std::stack<Pos> path = mCtrl->getPathTo(nearestBonus);

	//choose action
	float can= Grid::SideLen/mCtrl->GetCharacter()->GetSpeed();//����Σ�� �ܷ�ͨ��
	if(path.empty() || (!path.empty()&& mCtrl->GetDangerGrid()->GetValue(path.top().col,path.top().row)<=can))
		return IDLE;
	else if(myPosition.GetCol()<path.top().GetCol() )
		return MOVE_RIGHT;
	else if(myPosition.GetCol()>path.top().GetCol() )
		return MOVE_LEFT;
	else if(myPosition.GetRow()>path.top().GetRow() )
		return MOVE_UP;
	else if(myPosition.GetRow()<path.top().GetRow())
		return MOVE_DOWN;
	return IDLE;
}

//////////////////////////////FreeState////////////////////////////
FreeState::FreeState(NPCController* ctrl):
State(ctrl)
{}

int FreeState::GetAction()
{
	GameStage* gs = (GameStage*)App::Inst().CurrentStage();
	if(gs->CanPass(mCtrl->GetCharacter()))
	{
		return mCtrl->GetCharacter()->GetCurState();
	}
	else
		return rand()%4;
}

///////////////////////////////DropBombState////////////////////////
DropBombState::DropBombState(NPCController* ctrl):
State(ctrl)
{}

int DropBombState::GetAction()
{
	if(rand()%100==0 && mCtrl->GetCharacter()->GetBombCnt()>0)
		return DROP_BOMB;
	else 
		return IDLE;
}

///////////////////////////////ClearPathState///////////////////////
ClearPathState::ClearPathState(NPCController* ctrl):
State(ctrl)
{}


int ClearPathState::GetAction()
{
	Pos myPosition = Pos(mCtrl->GetCharacter()->GetBoundingBox().Col(),mCtrl->GetCharacter()->GetBoundingBox().Row());
	Pos mostInterest = mCtrl->MostInterestPos();
	std::stack<Pos> path = mCtrl->getPathTo(mostInterest);

	//choose action
	float can= Grid::SideLen/mCtrl->GetCharacter()->GetSpeed();//����Σ�� �ܷ�ͨ��
	if(path.empty() ) 
	{
		return IDLE;
	}
	if(!path.empty() && mCtrl->GetDangerGrid()->GetValue(path.top().col,path.top().row)<=3.0)
		return IDLE;
	else if(myPosition.GetCol()<path.top().GetCol() )
	{
		return MOVE_RIGHT;
	}
	else if(myPosition.GetCol()>path.top().GetCol() )
	{
		return MOVE_LEFT;
	}
	else if(myPosition.GetRow()>path.top().GetRow() )
	{
		return MOVE_UP;
	}
	else if(myPosition.GetRow()<path.top().GetRow())
	{
		return MOVE_DOWN;
	}
	return IDLE;
}

///////////////////////////////////////////////////TriggerState/////////////////////
TriggerState::TriggerState(NPCController* ctrl):
State(ctrl)
{}

int TriggerState::GetAction()
{
	return TRIGGER_BOMB;
}

/////////////////////////////////////////////////AttackState///////////////////////

AttackState::AttackState(NPCController* ctrl):
State(ctrl)
{}

int AttackState::GetAction()
{
	return DROP_BOMB;
}
	