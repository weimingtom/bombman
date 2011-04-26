#include "AI.h"
#include "NPC.h"
#include "FSM.h"
#include"GameScene.h"

AI::AI( NPC* npc )
{
	this->npc = npc;
	fsm = new FSM();
}

AI::~AI()
{
	delete fsm;
}

void AI::Perception()
{
	currentMap = npc->GetGameScene()->GetMap();
}

void AI::Decision()
{
	fsm->Init();
	fsm->Update();
}

/*Action AI::GetAction()
{
	return action;
}*/
