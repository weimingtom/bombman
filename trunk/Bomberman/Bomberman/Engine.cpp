#include"Engine.h"
#include"HiResTimer.h"

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
			// we always update if there are any events, even if we're paused
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
	
}

void Engine::OnPrepare()
{
}

Scene* Engine::OnGetScene()
{
	return NULL;
}

void Engine::CheckInput(float deltaTime)
{
}