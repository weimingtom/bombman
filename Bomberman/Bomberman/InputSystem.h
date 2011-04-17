#pragma once 
#include<Windows.h>
#include"Keyboard.h"
#include"Mouse.h"

#define IS_USEKEYBOARD  1
#define IS_USEMOUSE     2

class InputSystem
{
public:
	InputSystem() { m_pKeyboard = NULL; m_pMouse = NULL;}
	~InputSystem() {}
	bool  Initialize(HWND hwnd, HINSTANCE appInstance, bool isExclusive, DWORD flags = 0);
	bool  Shutdown();

	void  AcquireAll();
	void  UnacquireAll();

	Keyboard* GetKeyboard() { return m_pKeyboard; }
	Mouse* GetMouse()    { return m_pMouse; }

	bool  Update();

	bool  KeyDown(char key) { return (m_pKeyboard && m_pKeyboard->KeyDown(key)); }
	bool  KeyUp(char key) { return (m_pKeyboard && m_pKeyboard->KeyUp(key)); }

	bool  ButtonDown(int button) { return (m_pMouse && m_pMouse->ButtonDown(button)); }
	bool  ButtonUp(int button) { return (m_pMouse && m_pMouse->ButtonUp(button)); }
	void  GetMouseMovement(int &dx, int &dy) { if (m_pMouse) m_pMouse->GetMovement(dx, dy); }

private:
	Keyboard  *m_pKeyboard;
	Mouse     *m_pMouse;

	LPDIRECTINPUT8 m_pDI;
};