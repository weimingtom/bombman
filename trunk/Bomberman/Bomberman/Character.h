#pragma once
#include "GameObject.h"

class Entity;
class GameScene;

enum Action
{
	INVALID_ACTION = -1,
	ACTION_WAIT,
	ACTION_MOVE_LEFT,
	ACTION_MOVE_RIGHT,
	ACTION_MOVE_UP,
	ACTION_MOVE_DOWN,
	ACTION_DROP_BOMB,
	ACTION_TRIGGER_BOMB,
	NUM_ACTIONS,
};

class GameScene;
class Character : public GameObject
{
public:
	void DoAction(Action action);
	GameScene* GetGameScene();
protected:
	Entity* entity;
	GameScene* gameScene;
};