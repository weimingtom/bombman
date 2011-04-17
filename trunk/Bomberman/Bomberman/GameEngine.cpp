#include"GameEngine.h"

GameEngine::GameEngine()
{
	currentScene = new Scene();
}

GameEngine::~GameEngine()
{
	delete currentScene;
	currentScene = NULL;
}

void GameEngine::OnPrepare()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}


void GameEngine::OnKeyDown(int nVirtKey)
{
	switch (nVirtKey)
	{
	case VK_UP:
		break;

	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
	default:
		break;
	}	
}

Scene* GameEngine::OnGetScene()
{
	return currentScene;
}
