#pragma once
#include <vector>

enum GridState
{
	Empty, Dwall,Uwall,Player,NPC
};

struct GridInfo
{
	GridState gridState;
	
	float bAddBomb;
	float bAddFlame;
	float bFaster;
	float bPush;
	float bTrigger;
	float mSlower;
	float mDrop;

	int col;
	int row;
};

class Map
{
public:
	Map();
	~Map();
	void Load();
	void Unload();
private:
	std::vector<GridInfo> grids;
};