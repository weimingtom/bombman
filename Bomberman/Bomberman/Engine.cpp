#include"Engine.h"
#include"Scene.h"
#include"HiResTimer.h"
#include"InputSystem.h"

LRESULT Engine::EnterMessageLoop()
{
	//	Message loop
	MSG msg;
	timer = new CHiResTimer();

	timer->Init();

	for (;;)
	{	
		GameCycle(timer->GetElapsedSeconds(1));
		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage (&msg, NULL, 0, 0))
			{
				delete timer;
				return msg.wParam;
			}
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
	}
	delete timer;
	return msg.wParam;
}

void Engine::GameCycle(float deltaTime)
{

	if (useDInput)
		CheckInput(deltaTime);
	OnPrepare();
	
	currentScene->Prepare();
	currentScene->Animate(deltaTime);
	currentScene->Render();
	
	SwapBuffers(hDC);
}

Scene* Engine::OnGetScene()
{
	return NULL;
}

void Engine::CheckInput(float deltaTime)
{
	static float buttonDelta = 0.0f;

	int mouseDeltaX, mouseDeltaY;

	buttonDelta -= deltaTime;

	if (buttonDelta < 0.0f)
		buttonDelta = 0.0f;

	inputSystem->Update();
	inputSystem->GetMouseMovement(mouseDeltaX, mouseDeltaY);
	OnMouseMove(mouseDeltaX, mouseDeltaY);

	if (inputSystem->KeyDown(DIK_UP))
		OnKeyDown(VK_UP);
	if (inputSystem->KeyDown(DIK_DOWN))
		OnKeyDown(VK_DOWN);
	if (inputSystem->KeyDown(DIK_LEFT))
		OnKeyDown(VK_LEFT);
	if (inputSystem->KeyDown(DIK_RIGHT))
		OnKeyDown(VK_RIGHT);
	if (inputSystem->KeyDown(DIK_ADD))
		OnKeyDown(VK_ADD);
	if (inputSystem->KeyDown(DIK_SUBTRACT))
		OnKeyDown(VK_SUBTRACT);
	if (inputSystem->KeyDown(DIK_ESCAPE))
		OnKeyDown(VK_ESCAPE);
	if (inputSystem->ButtonDown(0))
	{
		if (buttonDelta == 0.0f)
		{
			OnMouseDownL(0,0);
			buttonDelta = 0.5f;
		}
	}
}