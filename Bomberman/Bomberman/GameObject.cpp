#include"GameObject.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <gl/glut.h>

GameObject::GameObject()
{
	toBeDelete = false;
}

Position GameObject::GetPos2D()
{
	return pos2D;
}

void GameObject::SetPos2D( Position pos )
{
	pos2D = pos;
}

Vector GameObject::GetPos3D()
{
	return pos3D;
}

void GameObject::SetPos3D( Vector pos )
{
	pos3D = pos;
}

Vector GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetVelocity( Vector vel )
{
	velocity = vel;
}

Vector GameObject::GetSize()
{
	return size;
}

void GameObject::SetSize( scalar_t siz )
{
	size = siz;
}

void GameObject::Render()
{
	glPushMatrix();
	OnRender();		// Render this object
	
	if (HasChild())		// Render children
		((GameObject*)GetChild())->Render();
	glPopMatrix();

	// Render siblings
	if (HasParent() && !IsLastChild())
		((GameObject*)GetFollowing())->Render();
}

void GameObject::Animate( scalar_t deltaTime )
{
	OnAnimate(deltaTime);		// animate this object

	// animate children
	if (HasChild())
		((GameObject*)GetChild())->Animate(deltaTime);

	// animate siblings
	if (HasParent() && !IsLastChild())
		((GameObject*)GetFollowing())->Animate(deltaTime);

	if (toBeDelete)
		delete this;
}

void GameObject::ProcessCollision( GameObject* obj )
{
	//to be considered
	/*if (((obj->pos3D - pos3D).Length() <= (obj->size + size)) &&
		(obj != ((GameObject*)this)))
	{
		OnCollision(obj);		// perform this object's collision with obj

		// test child collisions with obj
		if (HasChild())
			((GameObject*)GetChild())->ProcessCollision(obj);

		// test sibling collisions with obj
		if (HasParent() && !IsLastChild())
			((GameObject*)GetFollowing())->ProcessCollision(obj);
	}

	// if obj has children, check collisions with these children
	if (obj->HasChild())
		ProcessCollision((GameObject*)(obj->GetChild()));*/

	// if obj has siblings, check collisions with these siblings
	if (obj->HasParent() && !obj->IsLastChild())
		ProcessCollision((GameObject*)(obj->GetFollowing()));
}

void GameObject::Prepare()
{
	OnPrepare();						// prepare this object

	if (HasChild())					// prepare children
		((GameObject*)GetChild())->Prepare();

	if (HasParent() && !IsLastChild())		// prepare siblings
		((GameObject*)GetFollowing())->Prepare();
}

GameObject* GameObject::FindRoot()
{
	if (GetParent())
			return ((GameObject*)GetParent())->FindRoot();
	return this;
}

void GameObject::OnAnimate( float deltaTime )
{
	pos3D += velocity*deltaTime;
}

void GameObject::OnPrepare()
{
	ProcessCollision(FindRoot());
}
