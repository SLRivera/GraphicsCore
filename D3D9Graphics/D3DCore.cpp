/*!
 * \file D3DCore.cpp
 *
 * \author Sam Rivera
 * \date 9/27/2015
 *
 * 
 */
#include "GFX.h"
#include "D3DCore.h"
#include "Text.h"
#include "resource.h"

using std::vector;
using namespace GFXCore;
using namespace GSP420;

D3DCore*	D3DCore::pInstance = NULL;

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (D3DCore::get()->getDevice())
		return D3DCore::get()->msgProc(hwnd, msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

D3DCore::D3DCore() :
pD3DDevice(NULL),
pD3DObject(NULL),
nWidth(0),
nHeight(0),
dwRequestedVP(0),
hHwnd(NULL),
hInstance(NULL)
{
	memset(&presentParams, NULL, sizeof(D3DPRESENT_PARAMETERS));
}


D3DCore::~D3DCore()
{
}

bool D3DCore::initMainWnd(const HINSTANCE hInst, const wchar_t* wndCaption,
										const int width, const int height)
{
	hInstance = hInst;
	// TODO: FIX ME, returns NULL
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	WNDCLASSEX wc;
	memset(&wc, NULL, sizeof(WNDCLASSEX));
	wc.lpszClassName	= L"GSP420EngineClass";
	wc.cbSize				= sizeof(WNDCLASSEX);
	wc.style					= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= MainWndProc;
	wc.cbClsExtra			= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance			= hInstance;
	wc.hIcon				= hIcon;
	wc.hIconSm			= hIcon;
	wc.hCursor				= LoadCursor(0, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	= 0;

	if (!RegisterClassEx(&wc)) {
		ErrorMsg(L"RegisterClassEx Failure!", L"D3DCore::initMainWindow");
		PostQuitMessage(0);
		return false;
	}

	wcscpy_s(strMainWndCaption, wndCaption);
	nHeight = height;
	nWidth = width;

	hHwnd = CreateWindow(wc.lpszClassName, strMainWndCaption,
									WS_POPUPWINDOW,
									(GetSystemMetrics(SM_CXSCREEN) >> 1) - (nWidth >> 1),
									(GetSystemMetrics(SM_CYSCREEN) >> 1) - (nHeight >> 1),
									nWidth, nHeight,
									NULL, NULL,
									hInstance, NULL);
	if (NULL == hHwnd) {
		ErrorMsg(L"CreateWindow Failure", L"D3DCore::initMainWindow");
		PostQuitMessage(0);
		return false;
	}

	ShowWindow(hHwnd, SW_SHOW);
	UpdateWindow(hHwnd);

	return true;
}

bool D3DCore::initDirect3D(const D3DDEVTYPE requestedDevtype, const DWORD requestedVP)
{
	pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == pD3DObject) {
		ErrorMsg(L"D3D Object Creation Failure!", L"D3DCore::initDirect3D");
		PostQuitMessage(0);
		return false;
	}

	deviceType = requestedDevtype;
	dwRequestedVP = requestedVP;

	D3DDISPLAYMODE mode;
	pD3DObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	HR(pD3DObject->CheckDeviceType(D3DADAPTER_DEFAULT, deviceType, mode.Format, mode.Format, true));
	HR(pD3DObject->CheckDeviceType(D3DADAPTER_DEFAULT, deviceType, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, false));

	D3DCAPS9 caps;
	HR(pD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps));

	DWORD devBehaviorFlags = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		devBehaviorFlags |= dwRequestedVP;
	else
		devBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	if (caps.DevCaps & D3DDEVCAPS_PUREDEVICE && devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		devBehaviorFlags |= D3DCREATE_PUREDEVICE;

	presentParams.BackBufferWidth	= 0;
	presentParams.BackBufferHeight	= 0;
	presentParams.BackBufferFormat	= D3DFMT_UNKNOWN;
	presentParams.BackBufferCount		= 1;
	presentParams.MultiSampleType	= D3DMULTISAMPLE_NONE;
	presentParams.MultiSampleQuality = 0;
	presentParams.SwapEffect			= D3DSWAPEFFECT_DISCARD;
	presentParams.hDeviceWindow		= hHwnd;
	presentParams.Windowed				= true;
	presentParams.EnableAutoDepthStencil	= true;
	presentParams.AutoDepthStencilFormat	= D3DFMT_D16;
	presentParams.Flags							= 0;
	presentParams.FullScreen_RefreshRateInHz = D3DPRESENT_INTERVAL_DEFAULT;
#if 1
	presentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
#else
	presentParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
#endif

	HR(pD3DObject->CreateDevice(D3DADAPTER_DEFAULT,
													deviceType, hHwnd, devBehaviorFlags,
													&presentParams, &pD3DDevice));

	return true;
}

bool D3DCore::initGfxCore(const HINSTANCE hInst, const wchar_t* wndCaption, const int width, const int height, 
										  const D3DDEVTYPE requestedDevtype, const DWORD requestedVP)
{
	if (false == initMainWnd(hInst, wndCaption, width, height))
		return false;
	if (false == initDirect3D(requestedDevtype, requestedVP))
		return false;

	return true;
}

void D3DCore::onLostDevice()
{
	// does nothing for now, it is in GFX
}

void D3DCore::onResetDevice()
{
	// does nothing for now, it is in GFX
}


void GFXCore::D3DCore::shutdown()
{
	ReleaseCom(pD3DObject);
	ReleaseCom(pD3DDevice);
	UnregisterClass(L"GSP420EngineClass", hInstance); 
	PostQuitMessage(0);
	del();
}

bool GFXCore::D3DCore::isDeviceLost()
{
	HRESULT hr = pD3DDevice->TestCooperativeLevel();

	if (hr == D3DERR_DEVICELOST)
	{
		Sleep(20);
		return true;
	}
	else if (hr == D3DERR_DRIVERINTERNALERROR)
	{
		MessageBox(0, L"Internal Driver Error...Exiting", 0, 0);
		PostQuitMessage(0);
		return true;
	}
	else if (hr == D3DERR_DEVICENOTRESET)
	{
		GFX->onLostDevice();
		HR(pD3DDevice->Reset(&presentParams));
		GFX->onResetDevice();
		return false;
	}
	else
		return false;
}

LRESULT CALLBACK
D3DCore::msgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool minOrMaxed = false;

	RECT clientRect = { 0, 0, 0, 0 };
	switch (msg)
	{
	case WM_SIZE:
		if (pD3DDevice)
		{
			presentParams.BackBufferWidth = LOWORD(lParam);
			presentParams.BackBufferHeight = HIWORD(lParam);

			if (wParam == SIZE_MINIMIZED)
			{
				minOrMaxed = true;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				minOrMaxed = true;
				GFX->onLostDevice();
				HR(pD3DDevice->Reset(&presentParams));
				GFX->onResetDevice();
			}
			else if (wParam == SIZE_RESTORED)
			{
				if (minOrMaxed && D3DCore::get()->getPresentParams().Windowed)
				{
					GFX->onLostDevice();
					HR(pD3DDevice->Reset(&presentParams));
					GFX->onResetDevice();
				}
			
				minOrMaxed = false;
			}
		}
		return 0;

	case WM_EXITSIZEMOVE:
		GetClientRect(hHwnd, &clientRect);
		presentParams.BackBufferWidth = clientRect.right;
		presentParams.BackBufferHeight = clientRect.bottom;
		GFX->onLostDevice();
		HR(pD3DDevice->Reset(&presentParams));
		GFX->onResetDevice();

		return 0;

	case WM_CLOSE:
		DestroyWindow(hHwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		case VK_END:
			DestroyWindow(hHwnd);
			return 0;
		}
	}

	return DefWindowProc(hHwnd, msg, wParam, lParam);
}
