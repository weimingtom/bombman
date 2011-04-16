#pragma once
#include"GameObject.h"

class Texture;

class Button : public GameObject
{
public:
	Button();
	~Button();
	Texture* GetTexture();
protected:
	//virtual void OnClick();
	//virtual GameObject* HitTest(int mouseX,int mouseY);
private:
	Texture* texture;
};