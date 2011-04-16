#include "Mouse.h"

Mouse::Mouse(LPDIRECTINPUT8 pDI, HWND hwnd, bool isExclusive)
{
	if (FAILED(pDI->CreateDevice(GUID_SysMouse, &m_pDIDev, NULL)))
	{
		// error processing
	}

	if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIMouse)))
	{
		// error processing
	}

	DWORD flags;

	if (isExclusive)
		flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
	else
		flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;


	if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, flags)))
	{
		// error processing
	}

	if (FAILED(m_pDIDev->Acquire()))
	{
		// error processing
	}

	if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
	{
		// error processing
	}
}


bool Mouse::Update()
{
	if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
	{
		if (FAILED(m_pDIDev->Acquire()))
		{
			return false;
		}
		if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
		{
			return false;
		}
	}

	return true;
}




Mouse::~Mouse()
{
	if (m_pDIDev)
	{
		m_pDIDev->Unacquire();
		m_pDIDev->Release();
	}
}


bool Mouse::Acquire()
{
	return (!FAILED(m_pDIDev->Acquire()));
}


bool Mouse::Unacquire()
{
	return (!FAILED(m_pDIDev->Unacquire()));
}