#pragma once
#include"GameObject.h"

class Map: public GameObject
{
public:
	Map();
	Map(int width,float rFactor);
	~Map();
	
	void Load();
	void Unload();

	//get series of property
protected:
	void OnAnimate(float deltaTime);
	void OnRender();
	void OnCollision(GameObject* obj);

private:
	int width;
	
	//more setting
};