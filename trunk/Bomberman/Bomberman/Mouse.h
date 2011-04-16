#pragma once
#include <Windows.h>
#include<dinput.h>

class Mouse
{
public:
	Mouse(LPDIRECTINPUT8 pDI, HWND hwnd, bool isExclusive = true);
	~Mouse();

	bool  ButtonDown(int button) { return (m_state.rgbButtons[button] & 0x80) ? true : false; }
	bool  ButtonUp(int button) { return (m_state.rgbButtons[button] & 0x80) ? false : true; }
	void  GetMovement(int &dx, int &dy) { dx = m_state.lX; dy = m_state.lY; }

	bool  Update();

	bool  Acquire();
	bool  Unacquire();

private:
	LPDIRECTINPUTDEVICE8  m_pDIDev;
	DIMOUSESTATE          m_state;
};