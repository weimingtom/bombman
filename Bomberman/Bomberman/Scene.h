#pragma once

class Map;
class AudioSystem;

class Scene
{
public:
	Scene();
	Scene(Map map);
	~Scene();

	Map* GetMap();
	AudioSystem* GetAudioSystem();
	void LoadScene();
	void UnloadScene();
	void Animate();
	void Render();
	void Prepare();
protected:
	virtual void OnAnimate(float deltaTime){};
	virtual void OnRender(){}
	virtual void OnPrepare(){};
private:
	Map* map;
	AudioSystem* audioSystem;
};