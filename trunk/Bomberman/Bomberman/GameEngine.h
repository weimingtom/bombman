#pragma once
#include"Engine.h"

class Scene;

class GameEngine: public Engine
{
public:
	GameEngine(){}
	GameEngine(const TCHAR* windowName, bool fullScreen, int width, int height, int b):Engine(windowName, fullScreen,width, height, b)
	{
		//implement
	}
	~GameEngine(){}
protected:
	//void OnPrepare();
	//Scene* OnGetScene();
	
	//mouse and key
private:
	Scene* gameScene;

};