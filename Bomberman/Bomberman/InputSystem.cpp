#include "InputSystem.h" 

bool InputSystem::Initialize(HWND hwnd, HINSTANCE appInstance, bool isExclusive, DWORD flags)
{
	if (FAILED(DirectInput8Create(appInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8W,
		(void **)&m_pDI,
		NULL)))
		return false;

	if (flags & IS_USEKEYBOARD)
	{
		m_pKeyboard = new Keyboard(m_pDI, hwnd);
	}
	if (flags & IS_USEMOUSE)
	{
		m_pMouse = new Mouse(m_pDI, hwnd, true);
	}
	return true;
}


bool InputSystem::Shutdown()
{
	UnacquireAll();
	if (m_pKeyboard)
	{
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	if (m_pKeyboard)
	{
		delete m_pMouse;
		m_pMouse = NULL;
	}

	if (FAILED(m_pDI->Release()))
		return false;

	return true;
}

bool InputSystem::Update()
{
	if (m_pKeyboard)
		m_pKeyboard->Update();
	if (m_pMouse)
		m_pMouse->Update();
	return true;
}


void InputSystem::AcquireAll()
{
	if (m_pKeyboard)
		m_pKeyboard->Acquire();
	if (m_pMouse)
		m_pMouse->Acquire();
}


void InputSystem::UnacquireAll()
{
	if (m_pKeyboard)
		m_pKeyboard->Unacquire();
	if (m_pMouse)
		m_pMouse->Unacquire();
}