#include "AI.h"
#include "NPC.h"
#include "FSM.h"
#include"GameScene.h"
#include "Character.h"

AI::AI( NPC* npc )
{
	this->npc = npc;
	fsm = new FSM();
	fsm->Init();
	currentMap = this->npc->GetGameScene()->GetMap();
}

AI::~AI()
{
	delete fsm;
}

void AI::Decision()
{
	fsm->Update();
}

Action AI::GetAction()
{
	return action;
}
