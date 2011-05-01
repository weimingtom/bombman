#pragma once
#include"Node.h"
#include"Vector.h"
#include<Windows.h>

//2d pos
struct Position
{
	int X;
	int Y;
};

class GameObject: public Node
{
public:
	GameObject();
	~GameObject(){}

	Position GetPos2D();
	void SetPos2D(Position pos);
	Vector GetPos3D();
	void SetPos3D(Vector pos);
	Vector GetVelocity();
	void SetVelocity(Vector vel);
	Vector GetSize();
	void SetSize(scalar_t siz);

	virtual void Load() {}
	virtual void Unload() {}

	void Render();
	void Animate(scalar_t deltaTime);
	void ProcessCollision(GameObject* obj);
	void Prepare();
	
	GameObject* FindRoot();

protected:
	virtual void OnAnimate(float deltaTime);
	virtual void OnRender() {}
	virtual void OnCollision(GameObject* obj){}
	virtual void OnPrepare();

	bool toBeDelete;

	Position pos2D;
	Vector pos3D;
	Vector velocity;
	scalar_t size;
};