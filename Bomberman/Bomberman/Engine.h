#pragma once
#include"GlWindow.h"
#include"HiResTimer.h"

class Scene;

class Engine : public GlWindow
{
public:
	Engine(){}
	Engine(const TCHAR* windowName, bool fullScreen, int width, int height, int b):GlWindow(windowName,fullScreen,width,height,b){}
	~Engine(){}
	CHiResTimer *timer;	
	LRESULT EnterMessageLoop();
protected:
	//CHiResTimer *timer;
	virtual void GameCycle(float deltaTime);
	virtual void OnPrepare();
	virtual Scene* OnGetScene();
	virtual void CheckInput(float deltaTime);
private:
	Scene* gameScene;
};