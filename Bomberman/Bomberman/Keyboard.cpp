#include"Keyboard.h"

Keyboard::Keyboard(LPDIRECTINPUT8 pDI, HWND hwnd)
{
	if (FAILED(pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDev, NULL)))
	{
		// error processing
	}

	if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIKeyboard)))
	{
		// error processing
	}

	if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		// error processing
	}

	if (FAILED(m_pDIDev->Acquire()))
	{
		// error processing
	}

	Clear();
}

bool Keyboard::Acquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Acquire()));
}

bool Keyboard::Unacquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Unacquire()));
}


bool Keyboard::Update()
{
	if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
	{
		if (FAILED(m_pDIDev->Acquire()))
		{
			return false;
		}
		if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
		{
			return false;
		}
	}
	return true;
}