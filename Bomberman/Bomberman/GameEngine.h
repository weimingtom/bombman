#pragma once
#include"Engine.h"
#include"Scene.h"

class Scene;

class GameEngine: public Engine
{
public:
	GameEngine();
	GameEngine(const TCHAR* windowName, bool fullScreen, int width, int height, int b):Engine(windowName, fullScreen,width, height, b)
	{
		//currentScene = new Scene();
	}
	~GameEngine();

protected:
	virtual void OnPrepare();
	virtual Scene* OnGetScene();
	virtual void OnKeyDown(int nVirkey);
};
