/*!
* \file DirectInput.h
*
* \author Sam Rivera
* \date September 2015
*
* Last Revision: 9/23/15
*/
#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")


class DirectInput
{
public:
	DirectInput(HINSTANCE hInst, DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	~DirectInput();

	void poll();
	bool keyDown(unsigned char key);
	bool mouseButtonDown(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();

private:
	// Make private to prevent copying of members of this class.
	DirectInput(const DirectInput& rhs);
	DirectInput& operator=(const DirectInput& rhs);
		
private:
	IDirectInput8*       mDInput;

	IDirectInputDevice8* mKeyboard;
	char                 mKeyboardState[256]; 

	IDirectInputDevice8* mMouse;
	DIMOUSESTATE2        mMouseState;
};
extern DirectInput* gDInput;
