#pragma once
#include"GameObject.h"

class Map: public GameObject
{
public:
	Map();
	~Map();
	void Load();
	void Unload();
protected:
	// to be considered
private:
	//more setting
};