#include"Scene.h"

void Scene::Render()
{
	this->OnRender();
}

void Scene::Prepare()
{
	this->OnPrepare();
}

void Scene::Animate(float deltaTime)
{
	this->OnAnimate(deltaTime);
}

AudioSystem* Scene::GetAudioSystem()
{
	return audioSystem;
}

void Scene::SetAudioSystem( AudioSystem* audioSys )
{
	audioSystem = audioSys;
}

Scene::~Scene()
{
	//audioSystem->ShutDown();
	delete audioSystem;
}
