#pragma once
#include"AudioSystem.h"

class Scene
{
public:
	Scene(){}
	~Scene();

	void SetAudioSystem(AudioSystem* audioSys);
	AudioSystem* GetAudioSystem();
	void LoadScene();
	void UnloadScene();
	void Animate(float deltaTime);
	void Render();
	void Prepare();

protected:
	virtual void OnAnimate(float deltaTime){};
	virtual void OnRender(){}
	virtual void OnPrepare(){};

private:
	AudioSystem* audioSystem;
	/*CAudio *worldSound;           // the world ambient sound
	CAudio *gameMusic; */ 
};