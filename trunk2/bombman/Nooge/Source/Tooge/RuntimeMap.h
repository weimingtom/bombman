#pragma once

#include "Map.h"
#include "GameObjectContainer.h"
#include "GameObject.h"
#include "Ref.h"

class AIMap;
class RuntimeMap : public Map
{
public:
	RuntimeMap();
	void LoadMap();
	//virtual void Update();
	bool CanPass(GameObject* obj);
	//AIMap* CreateAIMap();
	void AddBomb(Ref<GameObject> bomb);

private:
	Ref<GameObject> mDwall;
	Ref<GameObject> mUwall;
	Ref<GameObject> mBomb;
	Ref<GameObject> mBonus;
	Ref<GameObject> mNPC;
	Ref<GameObject> mPlayer;
	Ref<Map> mMap;
};