/*!
 * \file Sprites.cpp
 *
 * \author Sam Rivera
 * \date 9/27/2015
 *
 * 
 */

#include "Sprites.h"

using std::vector;
using namespace GFXCore;

int Sprites::nIdGenerator = -1;

Sprites::Sprites() :
pSprite(NULL)
{
}


Sprites::~Sprites()
{
}

bool GFXCore::Sprites::init(IDirect3DDevice9* device, const int startNumSprites /*= 15*/)
{
	spriteList.reserve(startNumSprites);

	if ((FAILED(D3DXCreateSprite(device, &pSprite))))
		return false;

	return true;
}

int GFXCore::Sprites::loadSprite(IDirect3DDevice9* device, const wchar_t* fileName, Textures& textures, const D3DXVECTOR3& initPos, const bool centerIsTopLeft /*= true*/, const D3DCOLOR initColor /*= D3DCOLOR_RGBA(255, 255, 0, 255)*/, RECT* clipRect /*= NULL*/)
{
	for (unsigned int i = 0; i < spriteList.size(); ++i)
		if (0 == wcscmp(fileName, spriteList[i].strFileName))
			return i;

	SpriteData newSprite;
	memset(&newSprite, NULL, sizeof(SpriteData));
	wcscpy_s(newSprite.strFileName, MAX_FILE_NAME, fileName);

	newSprite.nTextureId = textures.loadTexture(device, fileName);
	if (-1 == newSprite.nTextureId)
		return -1;
	
	newSprite.position = initPos;
	newSprite.color = initColor;

	if (centerIsTopLeft) {
		newSprite.bCenterIsTopLeft = true;
	} else {
		newSprite.center.x = (float)textures.getTextureWidth(newSprite.nTextureId) * 0.5f;
		newSprite.center.y = (float)textures.getTextureHeight(newSprite.nTextureId) * 0.5f;
	}

	if (clipRect) {
		newSprite.clipRect = *clipRect;
		newSprite.bHasClipRect = true;
	}

	spriteList.push_back(newSprite);

	return ++nIdGenerator;
}

void Sprites::shutdow()
{
	ReleaseCom(pSprite);

	spriteList.clear();
	spriteList.resize(0);
}

void GFXCore::Sprites::render(const int id, Textures& textures)
{
#if defined (_DEBUG) | defined(DEBUG)
	CHECK_OUT_OF_BOUNDS(id, (int)spriteList.size());
#endif

	HRESULT hr = pSprite->Draw(textures.getTexture(spriteList[id].nTextureId),
											spriteList[id].bHasClipRect == true ? &spriteList[id].clipRect : NULL,
											spriteList[id].bCenterIsTopLeft == true ? NULL : &spriteList[id].center,
											&spriteList[id].position,
											spriteList[id].color);

	if (FAILED(hr))
		ErrorMsg(L"Sprite Draw Failure!", L"Sprites::render()");
}

void GFXCore::Sprites::update(const int id, const D3DXVECTOR3& newPos)
{
#if defined (_DEBUG) | defined(DEBUG)
	CHECK_OUT_OF_BOUNDS(id, (int)spriteList.size());
#endif

	spriteList[id].position = newPos;
}


