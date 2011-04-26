#pragma once

class NPC;
class FSM;
class Map;

//enum Action;

class AI
{
public:
	AI(NPC* npc);
	~AI();
	void Perception();
	void Decision();
	//Action GetAction();
private:
	NPC* npc;
	FSM* fsm;
	Map* currentMap;
	//Action action;

};