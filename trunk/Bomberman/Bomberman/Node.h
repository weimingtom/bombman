#pragma once

class Node
{
public:
	Node* GetParent();
	Node* GetChild();
	Node* GetPreceding();
	Node* GetFollowing();

	Node();
	Node(Node* node);
	virtual ~Node();

	bool HasParent();
	bool HasChild();
	bool IsFirstChild();
	bool IsLastChild();
	
	void AttachToParent(Node* newParent);
	void AttachChild(Node* child);
	void Detach();//detach from parent

	int Cnt();
private:
	Node* parent;
	Node* child;
	Node* preceding;
	Node* following;

};