#include "..\\D3D9Graphics\\GFX.h"

using namespace GFXCore;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);
	UNREFERENCED_PARAMETER(showCmd);

	// Enable run-time memory check for debug builds.
// #if defined(DEBUG) | defined(_DEBUG)
// 	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// #endif

	if (false == GFX->initGFX(hInstance, L"test"))
		return 0;
	if (false == GFX->initModules())
		return 0;

	int m = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\PlayerSPaceShipV2.X", D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	int n = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\PlayerSPaceShipV2.X", D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	GFX->loadSprite(L"..\\GraphicsCoreTests\\Assets\\testsprite.jpg"/*, true, D3DXVECTOR3(100.0f, 400.0f, 0.0f)*/);
	//GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\BoxTest.X", D3DXVECTOR3(0.0f, 0.0f, 100.f));
	//GFX->cameraSetPos(D3DXVECTOR3(0.0f, 0.0f, -0.0f));
	GFX->cameraSetLens(GFX->windowWidth(), GFX->windowHeight(), -1000.0f, 1000.0f);

	DirectInput di(hInstance, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	gDInput = &di;

	FontData newFont;
	memset(&newFont, NULL, sizeof(FontData));
	newFont.bItalics = false;
	newFont.nFontHeight = 20;
	newFont.nFontWidth = 10;
	wcscpy_s(newFont.strFontName, L"Delicious-Roman");
	newFont.textBoxDimens = { 00, 00, 300, 200 };
	newFont.textColor = D3DCOLOR_XRGB(255, 0, 0);
	int fontId = GFX->loadFont(newFont);

	MSG msg;
	memset(&msg, NULL, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		gDInput->poll();
		static float x = 0.0f;
		if (gDInput->keyDown(DIK_A))
			x += 0.01f;
		GFX->beginScene(D3DCOLOR_XRGB(0, 0, 100));
	//	GFX->updateCamera(1.0f);
		GFX->updateModel(m, D3DXVECTOR3(x, 200.0f, 0.0f), true, true, D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
		GFX->renderModel(m);
		GFX->renderText(fontId, L"This now works!");
		GFX->updateModel(n, D3DXVECTOR3(-x, -200.0f, 0.0f), true, true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
		GFX->renderModel(n);
		//GFX->renderSprites();
		GFX->endScene();

	}

	GFX->shutdown();

	return 0;
}