#pragma once
#include<vector>
//#include<iostream>
#include"Scene.h"
using namespace std;

class Button;
class Texture;

class MenuScene : public Scene
{
public:
	MenuScene(){}
	~MenuScene();
	virtual void LoadScene();
	virtual void UnloadScene();
protected:
	virtual void OnRender();
private:
	vector<Button*> buttons;
	Texture* bgImage;
};