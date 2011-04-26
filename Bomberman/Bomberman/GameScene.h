#pragma once
#include "Scene.h"

class Map;

class GameScene: public Scene
{
public:
	Map* GetMap();
private:
	Map* map;
};