/*!
* \file Sprites.h
*
* \author Sam Rivera
* \date September 2015
*
* Last Revision: 9/23/15
*/
#pragma once
#include <vector>
#include "D3DUtils.h"
#include "Textures.h"


namespace GFXCore
{
	struct SpriteData {
		wchar_t				strFileName[MAX_FILE_NAME];
		D3DXVECTOR3	center;
		D3DXVECTOR3	position;
		RECT					clipRect;
		D3DCOLOR			color;
		int						nTextureId;
		bool					bHasClipRect;
		bool					bCenterIsTopLeft;
	};

	class Sprites 
	{
	public:
		bool init(IDirect3DDevice9* device, const int startNumSprites = 15);
		int loadSprite(IDirect3DDevice9* device, const wchar_t* fileName, 
							Textures& textures, 
							const D3DXVECTOR3& initPos, const bool centerIsTopLeft, 
							const D3DCOLOR initColor,
							RECT* clipRect);
		void update(const int id, const D3DXVECTOR3& newPos);
		void shutdow();
		void render(const int id, Textures& textures);
		
		inline void beginDraw();
		inline void endDraw();
		inline void onLostDevice();
		inline void onResetDevice();

		inline SpriteData&	getSprite(const int id);

		Sprites();
		~Sprites();

	protected:
		std::vector<SpriteData>	spriteList;

		ID3DXSprite*		pSprite;

	private:
		static int nIdGenerator;
	};

	// TODO: Check for DEBUG out of bounds check
	SpriteData& Sprites::getSprite(const int id)		{ return spriteList[id]; }

	void Sprites::beginDraw()	{ pSprite->Begin(D3DXSPRITE_ALPHABLEND); }
	void Sprites::endDraw() { pSprite->End(); }

	void GFXCore::Sprites::onLostDevice() {
		if (pSprite)
			HR(pSprite->OnLostDevice());
	}

	void GFXCore::Sprites::onResetDevice() {
		if (pSprite)
			HR(pSprite->OnResetDevice());
	}
}