/*!
 * \file DirectInput.cpp
 *
 * \author Sam Rivera
 * \date 9/27/2015
 *
 * 
 */


#include "D3DUtils.h"
#include "DirectInput.h"

DirectInput* gDInput = 0;

DirectInput::DirectInput(HINSTANCE hInst, DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
	ZeroMemory(&mMouseState, sizeof(mMouseState));

	UNREFERENCED_PARAMETER(keyboardCoopFlags);
	UNREFERENCED_PARAMETER(mouseCoopFlags);

	HR(DirectInput8Create(hInst, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&mDInput, 0));

	HR(mDInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, 0));
	HR(mKeyboard->SetDataFormat(&c_dfDIKeyboard));
//	HR(mKeyboard->SetCooperativeLevel(gd3dApp->getMainWnd(), keyboardCoopFlags));
	HR(mKeyboard->Acquire());

	HR(mDInput->CreateDevice(GUID_SysMouse, &mMouse, 0));
	HR(mMouse->SetDataFormat(&c_dfDIMouse2));
//	HR(mMouse->SetCooperativeLevel(gd3dApp->getMainWnd(), mouseCoopFlags));
	HR(mMouse->Acquire());
}

DirectInput::~DirectInput()
{
	ReleaseCom(mDInput);
	mKeyboard->Unacquire();
	mMouse->Unacquire();
	ReleaseCom(mKeyboard);
	ReleaseCom(mMouse);
}

void DirectInput::poll()
{
	// Poll keyboard.
	HRESULT hr = mKeyboard->GetDeviceState(sizeof(mKeyboardState), (void**)&mKeyboardState); 
	if (FAILED(hr))
	{
		// Keyboard lost, zero out keyboard data structure.
		ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

		 // Try to acquire for next time we poll.
		hr = mKeyboard->Acquire();
	}

	// Poll mouse.
	hr = mMouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&mMouseState); 
	if (FAILED(hr))
	{
		// Mouse lost, zero out mouse data structure.
		ZeroMemory(&mMouseState, sizeof(mMouseState));

		// Try to acquire for next time we poll.
		hr = mMouse->Acquire(); 
	}
}

bool DirectInput::keyDown(unsigned char key)
{
	return (mKeyboardState[key] & 0x80) != 0;
}

bool DirectInput::mouseButtonDown(int button)
{
	return (mMouseState.rgbButtons[button] & 0x80) != 0;
}

float DirectInput::mouseDX()
{
	return (float)mMouseState.lX;
}

float DirectInput::mouseDY()
{
	return (float)mMouseState.lY;
}

float DirectInput::mouseDZ()
{
	return (float)mMouseState.lZ;
}