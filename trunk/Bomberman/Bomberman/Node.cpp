#include"Node.h"
#include <stdio.h>

Node::Node()
{
	parent = child = NULL;
	preceding = following = this;
}

Node::Node( Node* node )
{
	parent = child = NULL;	// setup and attach this node to node
	preceding = following = this;
	AttachToParent(node);
}

Node::~Node()
{
	Detach();				// detach from hierarchy

	while (child)		// delete all children
	{
		delete child;
	}
}

Node* Node::GetParent()
{
	return parent;
}

Node* Node::GetChild()
{
	return child;
}

Node* Node::GetPreceding()
{
	return preceding;
}

Node* Node::GetFollowing()
{
	return following;
}

bool Node::HasParent()
{
	return parent != NULL;
}

bool Node::HasChild()
{
	return child != NULL;
}

bool Node::IsFirstChild()
{
	if (parent)
		return (parent->child == this);
	else
		return false;
}

bool Node::IsLastChild()
{
	if (parent)
		return (parent->child->preceding == this);
	else
		return false;
}

void Node::AttachToParent( Node* newParent )
{
	if (parent)
		Detach();

	parent = newParent;

	if (parent->child)
	{
		preceding = parent->child->preceding;
		following = parent->child;
		parent->child->preceding->following = this;
		parent->child->preceding = this;
	}
	else
	{
		parent->child = this;		// this is the first child
	}
}

void Node::AttachChild( Node* newChild )
{
	if (newChild->HasParent())
		newChild->Detach();

	newChild->parent = this;

	if (child)
	{
		newChild->preceding = child->preceding;
		newChild->following = child;
		child->preceding->following = newChild;
		child->preceding = newChild;
	}
	else
		child = newChild;
}

void Node::Detach()
{
	if (parent && parent->child == this)
	{
		if (following != this)
			parent->child = following;
		else
			parent->child = NULL;		// no next child
	}

	// get rid of links
	preceding->following = following;
	following->preceding = preceding;

	// now this node is not in the list
	preceding = this;
	following = this;
}

int Node::Cnt()
{
	if (child)
		return child->Cnt() + 1;
	else
		return 1;
}

