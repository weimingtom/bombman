#include<windows.h>
#include"GlWindow.h"
#include"GameEngine.h"
#include"Engine.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	int loopRet;

	CoInitialize(NULL);

	if (!GlWindow::RegisterWindow(hInst))
	{
		MessageBox(NULL, L"Failed to register window class", L"Error", MB_OK);
		return -1;
	}

	GameEngine *engine = NULL;

	try
	{
		engine = new GameEngine(L"Bomberman", FALSE, 800, 600, 16);

		loopRet = engine->EnterMessageLoop();

		delete engine;

		return loopRet;
	}
	catch(TCHAR* sz)
	{	
		MessageBox(NULL, sz, 0, 0);
		delete engine;
	}

	CoUninitialize();

	return -1;
}