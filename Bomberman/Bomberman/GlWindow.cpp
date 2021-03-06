#include"GlWindow.h"
#include"InputSystem.h"
#include"MenuScene.h"

void GlWindow::SetupPixelFormat()
{
	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd =
	{	
		sizeof(PIXELFORMATDESCRIPTOR),	// size
		1,							// version
		PFD_SUPPORT_OPENGL |
		PFD_DRAW_TO_WINDOW |
		PFD_DOUBLEBUFFER,				// support float-buffering
		PFD_TYPE_RGBA,					// color type
		16,							// prefered color depth
		0, 0, 0, 0, 0, 0,				// color bits (ignored)
		0,							// no alpha buffer
		0,							// alpha bits (ignored)
		0,							// no accumulation buffer
		0, 0, 0, 0,					// accum bits (ignored)
		16,							// depth buffer
		0,							// no stencil buffer
		0,							// no auxiliary buffers
		PFD_MAIN_PLANE,				// main layer
		0,							// reserved
		0, 0, 0,						// no layer, visible, damage masks
	};

	pixelFormat = ChoosePixelFormat(hDC, &pfd);

	SetPixelFormat(hDC, pixelFormat, &pfd);
}

void GlWindow::SetupPalette()
{
	int pixelFormat = GetPixelFormat(hDC);
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE* pPal;
	int paletteSize;

	int redMask, greenMask, blueMask;
	int i;

	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE)
		paletteSize = 1 << pfd.cColorBits;
	else
		return;

	pPal = (LOGPALETTE*)LocalAlloc(LPTR, sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
	pPal->palVersion = 0x300;
	pPal->palNumEntries = (short)paletteSize;

	//	build a simple RGB color palette
	redMask   = (1 << pfd.cRedBits)   - 1;
	greenMask = (1 << pfd.cGreenBits) - 1;
	blueMask  = (1 << pfd.cBlueBits)  - 1;

	for (i=0; i<paletteSize; ++i)
	{	pPal->palPalEntry[i].peRed = (BYTE)(
			(((i >> pfd.cRedShift) & redMask) * 255) / redMask);
		pPal->palPalEntry[i].peGreen = (BYTE)(
			(((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask);
		pPal->palPalEntry[i].peBlue = (BYTE)(
			(((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask);
		pPal->palPalEntry[i].peFlags = 0;
	}

	hPalette = CreatePalette(pPal);
	LocalFree(pPal);

	if (hPalette)
	{
		DeleteObject(SelectPalette(hDC, hPalette, FALSE));
		RealizePalette(hDC);
	}
}

void GlWindow::Destroy()
{
	if (hGLRC)
	{	
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hGLRC);
	}
	if (hPalette)
	{	
		DeleteObject(hPalette);
	}

	SetWindowLong(hWnd, GWL_USERDATA, (LONG)NULL);

	DestroyWindow(hWnd);

	EndFullScreen();
}

void GlWindow::PaletteChanged(WPARAM wParam)
{
	if (hGLRC && hPalette && (HWND)wParam != hWnd)
	{	
		wglMakeCurrent(hDC, hGLRC);
		UnrealizeObject(hPalette);
		SelectPalette(hDC, hPalette, FALSE);
		RealizePalette(hDC);
	}
}

BOOL GlWindow::QueryNewPalette()
{
	if (hGLRC && hPalette)
	{	
		wglMakeCurrent(hDC, hGLRC);
		UnrealizeObject(hPalette);
		SelectPalette(hDC, hPalette, FALSE);
		RealizePalette(hDC);

		return TRUE;
	}
	return FALSE;
}

void GlWindow::Paint()
{
	PAINTSTRUCT ps;
	BeginPaint(hWnd, &ps);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if (currentScene)
		currentScene->Render();
	::SwapBuffers(hDC);
	EndPaint(hWnd, &ps);
}

void GlWindow::Size()
{
	if (width > height)
		aspect = width;
	else
		aspect = height;

	if (hGLRC)
	{
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float nearClip = 1.0f / 100.0f;
		float farClip  = 256.0f;//127.0f;
		gluPerspective(54.0f, (float)width/(float)height, 0.1f, 200.0f);

		OnSize();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

float GlWindow::GetNormalizedPosX(LPARAM lParam)
{	
	return mouseSensitivity * (float)((short)LOWORD(lParam) - width/2) / aspect;
}

float GlWindow::GetNormalizedPosY(LPARAM lParam)
{
	return mouseSensitivity * (float)((short)HIWORD(lParam) - height/2) / aspect;
}

int GlWindow::GetMouseX(LPARAM lParam)
{
	return LOWORD(lParam);
}

int GlWindow::GetMouseY(LPARAM lParam)
{
	return HIWORD(lParam);
}


LRESULT APIENTRY WndProcOGL(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GlWindow *glWindow = (GlWindow*)GetWindowLong(hWnd, GWL_USERDATA);

	// make sure window has been created
	if ((glWindow == NULL) && (uMsg != WM_CREATE))
	{	
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	// dispatch messages
	switch (uMsg)
	{	
		case WM_CREATE:			// window creation
		{
			HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
			glWindow = (GlWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);

			SetWindowLong(hWnd, GWL_USERDATA, (LONG)glWindow);
			glWindow->hWnd = hWnd;

			return glWindow->Create();
		}
		case WM_QUIT:
		case WM_CLOSE:				// window close
			glWindow->Destroy();
			PostQuitMessage(0);
			return 0;

		case WM_DESTROY:			// window destroy
			glWindow->Destroy();
			PostQuitMessage(0);
			return 0;

		case WM_ACTIVATEAPP:		// activate app
			
			if (wParam)
			{	
				if (glWindow->fullscreen)
					glWindow->BeginFullScreen(glWindow->width, glWindow->height, glWindow->bits);

				ShowWindow(hWnd, SW_RESTORE);
				UpdateWindow(hWnd);
			}
			else
			{	
				ShowWindow(hWnd, SW_MINIMIZE);
				UpdateWindow(hWnd);
				
				if (glWindow->fullscreen)
					glWindow->EndFullScreen();
			}
			return 0;

		case WM_PALETTECHANGED:		// palette change
			glWindow->PaletteChanged(wParam);
			return 0;

		case WM_QUERYNEWPALETTE:		// new palette
			return glWindow->QueryNewPalette();

		case WM_PAINT:				// paint
			glWindow->Paint();
			return 0;

		case WM_SIZE:				// window size
			if (wParam != SIZE_MINIMIZED)
			{	
				glWindow->width = LOWORD(lParam);
				glWindow->height= HIWORD(lParam);
				glWindow->Size();
			}
			return 0;

		/*case WM_LBUTTONDOWN:		// left mouse button
			if (!glWindow->useDInput)
			{
				SetCapture(hWnd);
				Drag = lParam;
				bLMB = true;
				glWindow->OnMouseDownL(glWindow->GetNormalizedPosX(lParam), glWindow->GetNormalizedPosY(lParam));
			}
			break;*/

		/*case WM_RBUTTONDOWN:		// right mouse button
			if (!glWindow->useDInput)
			{
				SetCapture(hWnd);
				Drag = lParam;
				bRMB = true;
				glWindow->OnMouseDownR(glWindow->GetNormalizedPosX(lParam), glWindow->GetNormalizedPosY(lParam));
			}
			break;*/

		/*case WM_MOUSEMOVE:			// mouse movement
		{	
			if (!glWindow->useDInput)
			{
				int x  = glWindow->mouseX = glWindow->GetMouseX(lParam); 
				int y  = glWindow->mouseY = glWindow->GetMouseY(lParam);
				int dx = x - glWindow->GetMouseX(Drag);
				int dy = y - glWindow->GetMouseY(Drag);

				glWindow->OnMouseMove(x,y, glWindow->width, glWindow->height);

				if (GetCapture() == hWnd)
				{
					// left mouse button
					if (bLMB)
					{
						glWindow->OnMouseDragL(x,y, dx,dy);
					}
					
					// right mouse button
					if (bRMB)
					{	
						glWindow->OnMouseDragR(x,y, dx,dy);
					}

					Drag = lParam;
				}
			}
			break;
		}

		case WM_LBUTTONUP:			// left button release
			if (!glWindow->useDInput)
			{
				if ((GetCapture() == hWnd) && !bRMB)
				{
					ReleaseCapture();
				}

				bLMB = false;
				glWindow->OnMouseUpL();
			}
			break;

		case WM_RBUTTONUP:			// right button release
			if (!glWindow->useDInput)
			{
				if ((GetCapture() == hWnd) && !bLMB)
				{
					ReleaseCapture();
				}
				bRMB = false;
				glWindow->OnMouseUpR();
			}
			break;

		case WM_KEYUP:
			if (!glWindow->useDInput)
			{
				glWindow->OnKeyUp((int)wParam);
			}
			return 0;

		case WM_KEYDOWN:
			if (!glWindow->useDInput)
			{
				glWindow->OnKeyDown((int)wParam);
			}
			return 0;*/

		default:
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool GlWindow::RegisterWindow(HINSTANCE hInst)
{
	WNDCLASS windowClass;		// the window class

	windowClass.style		 = 0;
	windowClass.lpfnWndProc	 = WndProcOGL;
	windowClass.cbClsExtra	 = 0;
	windowClass.cbWndExtra	 = 0;
	windowClass.hInstance	 = hInst;
	windowClass.hIcon		 = 0;
	windowClass.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName	 = NULL;
	windowClass.lpszClassName = L"Engine";

	// register the window class
	if (!RegisterClass(&windowClass))
		return false;

	return true;
}

void GlWindow::BeginFullScreen(int width, int height, int bits)
{
	// Save current display state
	iPrevWidth = GetSystemMetrics(SM_CXSCREEN);
	iPrevHeight = GetSystemMetrics(SM_CYSCREEN);
	
	// Set new display state
	DEVMODE dm;
	memset(&dm, 0, sizeof(dm));
	dm.dmSize	= sizeof(DEVMODE);
	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
	dm.dmPelsWidth	= width;
	dm.dmPelsHeight = height;
	dm.dmBitsPerPel = bits;
	ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
}

void GlWindow::EndFullScreen()
{
	ChangeDisplaySettings(NULL, 0);
}

GlWindow::GlWindow(const TCHAR* szName, bool fscreen, int w, int h, int b)
{
	RECT windowRect;
	DWORD dwStyle;
	DWORD dwExStyle;
	
	currentScene = NULL;
	fullscreen = fscreen;
	width = w;
	height = h;
	bits = b;

	windowRect.left = (long)0;
	windowRect.right = (long)width;
	windowRect.top = (long)0;
	windowRect.bottom = (long)height;

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
	
	// create the window
	if (fullscreen)
	{
		BeginFullScreen(width, height, bits);
		hWnd = CreateWindowEx(NULL, L"Engine", szName, dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
						  0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
						  NULL, NULL, (HINSTANCE)GetModuleHandle(NULL), (void*)this);
	}
	else
	{

		hWnd = CreateWindowEx(NULL, L"Engine", szName, dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
						  0, 0, width, height, NULL, NULL, (HINSTANCE)GetModuleHandle(NULL),(void*)this);
	}

	if (hWnd == NULL) 
		throw "ERROR: Creating OpenGL Window!";

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	mouseSensitivity = 2.0f;

	inputSystem = new InputSystem();
	useDInput = inputSystem->Initialize(hWnd, (HINSTANCE)GetModuleHandle(NULL), true, IS_USEKEYBOARD | IS_USEMOUSE);

	SetForegroundWindow(hWnd);
	SetCapture(hWnd);
	SetFocus(hWnd);

	/*if (useDInput)
	{
		inputSystem->AcquireAll();
		inputSystem->Update();
	}*/

	ShowCursor(FALSE);
}

GlWindow::~GlWindow()
{
//	inputSystem->Shutdown();
	delete inputSystem;
//	inputSystem = NULL;

	if (hGLRC)
		Destroy();

	if (fullscreen)
		EndFullScreen();

	ShowCursor(TRUE);
}

bool GlWindow::Create()
{
	hDC = GetDC(hWnd);
	SetupPixelFormat();
	SetupPalette();
	hGLRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hGLRC);
	currentScene = new MenuScene();
	currentScene->LoadScene();
	return !OnCreate();
}