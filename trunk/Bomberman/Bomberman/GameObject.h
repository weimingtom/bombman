#pragma once
#include"Node.h"

struct Position
{
	int X;
	int Y;
};

class GameObject: public Node
{
public:
	GameObject();
	GameObject(Position& pos);
	~GameObject();
	
	//physical property

	void Render();
	void Update();
	void ProcessCollision(GameObject* obj);
	void Prepare();
	Node* FindRoot();
	Position GetPos();
protected:
	//virtual void OnUpdate(float deltaTime);
	virtual void OnRender();
	//virtual void OnCollision(GameObject* obj);
	//virtual void OnPrepare();
	//virtual void OnClick();
	//virtual GameObject* HitTest(int mouseX,int mouseY);
private:
	Position pos;
};