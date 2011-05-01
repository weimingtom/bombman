#pragma once
#include <vector>

enum GridState
{
	Empty, Dwall,Uwall,Player,NPC
};

struct GridInfo
{
	GridState gridState;
	int expBonus;
	int expDanger;
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
	bool CanPass(int gridId);
	void SetBomb(int gridId);
	//void HasBomb(int gridId);
private:
	std::vector<GridInfo> grids;
	float bAddBomb;
	float bAddFlame;
	float bFaster;
	float bPush;
	float bTrigger;
	float mSlower;
	float mDrop;
};