#pragma once
#define DIRECTINPUT_VERSION 0x0800
#define INITGUID 
#include <Guiddef.h>
#include<dinput.h>
#include<Windows.h>

class Keyboard
{
public:
	Keyboard(LPDIRECTINPUT8 pDI, HWND hwnd);
	~Keyboard();

	bool  KeyDown(char key) { return (m_keys[key] & 0x80) ? true : false; }
	bool  KeyUp(char key) { return (m_keys[key] & 0x80) ? false : true; }

	bool  Update();

	void  Clear() { ZeroMemory(m_keys, 256 * sizeof(char)); }

	bool  Acquire();
	bool  Unacquire();

private:
	LPDIRECTINPUTDEVICE8  m_pDIDev;
	char    m_keys[256];
};