#pragma once 
#include<Windows.h>

class InputSystem
{
public:
	InputSystem(){}
	~InputSystem(){}
	bool Initialize(HWND hwnd, HINSTANCE appInstance, bool isExclusive, DWORD flags = 0);
	bool ShutDown();

	void AcquireAll();
	void UnaquireAll();

	//keyboard 

	bool Update();
private:
	//Ckeyboard object
	
	//LPDIRECTINPUT8 m_pDI;

};