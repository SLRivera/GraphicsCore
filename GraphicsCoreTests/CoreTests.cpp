/*!
 * \file CoreTests.cpp
 *
 * \author Sam Rivera
 // also edited by Joshua Silvers
 * \date 9/27/2015
 *
 * 
 */
#include "..\\D3D9Graphics\\GFX.h"
#include "..\\D3D9Graphics\\ABC.h"
#include "Test.h"
using namespace GFXCore;
using namespace GSP420;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);
	UNREFERENCED_PARAMETER(showCmd);

	if (false == GFX->initGFX(hInstance, L"test"))
		return 0;
	if (false == GFX->initModules())
		return 0;

	int m = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\enemyBat.X", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	int n = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\enemySaucer.X", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	int o = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\finalBoss.x", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	int p = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\playerSpaceShip.X", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	/*int q = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\enemyBat.X", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	int r = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\enemySaucer.X", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	int s = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\finalBoss.x", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	int t = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\playerSpaceShip.X", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));*/
	//	GFX->cameraSetPos(D3DXVECTOR3(0.0f, 0.0f, -0.0f));
	// Test to see what happens when models overlap
	GFX->cameraSetLens(GFX->windowWidth(), GFX->windowHeight(), -1000.0f, 1000.0f);

	Test obj1 = Test(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.050f, 0.050f, 0.050f));
	obj1.init(m, -1);
	Test obj2 = Test(D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	obj2.init(n, -1);
	Test obj3 = Test(D3DXVECTOR3(0.0f, -300.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	obj3.init(o, -1);
	Test obj4 = Test(D3DXVECTOR3(400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	obj4.init(p, -1);
	Test obj5 = Test(D3DXVECTOR3(-400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	obj5.init(p, -1);
	/*Test obj6 = Test(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.050f, 0.050f, 0.050f));
	obj1.init(q, -1);
	Test obj7 = Test(D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	obj2.init(n, -1);
	Test obj8 = Test(D3DXVECTOR3(0.0f, -300.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	obj3.init(o, -1);
	Test obj9 = Test(D3DXVECTOR3(400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	obj4.init(p, -1);*/
	// Test to see what happens when models overlap
	

	DirectInput di(hInstance, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	gDInput = &di;

	FontData newFont;

	memset(&newFont, NULL, sizeof(FontData));
	newFont.bItalics = false;
	newFont.nFontHeight = 20;
	newFont.nFontWidth = 10;
	wcscpy_s(newFont.strFontName, L"Delicious-Roman");
	newFont.fontBoxDimens = { 00, 00, 300, 200 };
	newFont.fontColor = D3DCOLOR_XRGB(255, 0, 0);
	
	int fontId = GFX->loadFont(newFont);
	GFX->setTextForFont(fontId, L"This now works better!");
	/*int fontId = GFX->loadFont(newFont);
	GFX->setTextForFont(fontId, L"Tessssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssst");*/
	//This is a test to see what happens with large amounts of text

	memset(&newFont, NULL, sizeof(FontData));
	newFont.bItalics = false;
	newFont.nFontHeight = 20;
	newFont.nFontWidth = 10;
	wcscpy_s(newFont.strFontName, L"Delicious-Roman");
	newFont.fontBoxDimens = { 300, 200, 600, 400 };
	newFont.fontColor = D3DCOLOR_XRGB(0, 255, 0);

	int fontId2 = GFX->loadFont(newFont);
	GFX->setTextForFont(fontId2, L"Second Font");
	
	/*memset(&newFont, NULL, sizeof(FontData));
	newFont.bItalics = true;
	newFont.nFontHeight = 200;
	newFont.nFontWidth = 150;
	wcscpy_s(newFont.strFontName, L"Delicious-Roman");
	newFont.fontBoxDimens = { 00, 00, 300, 200 };
	newFont.fontColor = D3DCOLOR_XRGB(255, 0, 0);
	
	int fontId3 = GFX->loadFont(newFont);
	GFX->setTextForFont(fontId3, L"Some giant words");*/
	//Font size test

	int textIds[2];
	textIds[0] = fontId;
	textIds[1] = fontId2;
	//textIds[3] = fontId3;

	MSG msg;
	memset(&msg, NULL, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (GFX->isDeviceLost())
			break;

		GFX->addToModelRenderList(&obj5);
		GFX->addToModelRenderList(&obj1);
		GFX->addToModelRenderList(&obj2);
		GFX->addToModelRenderList(&obj3);
		GFX->addToModelRenderList(&obj4);
		//GFX->addToModelRenderList(&obj6);
	        //GFX->addToModelRenderList(&obj7);
	        //GFX->addToModelRenderList(&obj8);
	        //GFX->addToModelRenderList(&obj9);
		GFX->addToTextRenderList(textIds, 2);
		GFX->renderScene();

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GFX->shutdown();

	return 0;
}
