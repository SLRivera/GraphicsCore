/*!
* \file Textures.h
*
* \author Sam Rivera
* \date September 2015
*
* Last Revision: 9/23/15
*/
#pragma once
#include <vector>
#include "D3DUtils.h"

using std::vector;

namespace GFXCore
{
	struct TexureData {
		wchar_t		strFileName[MAX_FILE_NAME];
		IDirect3DTexture9* pTex;
		int		nWidth;
		int		nHeight;
	};
	
	class Textures
	{
	public:
		bool init(const int startNumTex);
		int loadTexture(IDirect3DDevice9* device, const wchar_t* fileName);
		void shutdown();
		
		inline IDirect3DTexture9* getTexture(const int id);
		inline int getTextureWidth(const int id) const;
		inline int getTextureHeight(const int id) const;

		Textures();
		~Textures();

	protected:
		vector<TexureData>	texList;

	private:
		static int nIdGenerator;
	};

	// TODO: Check of DEBUG out of bounds
	IDirect3DTexture9* GFXCore::Textures::getTexture(const int id)	{ return texList[id].pTex; }
	// TODO: Check for DEBUG out of bounds check
	int Textures::getTextureHeight(const int id)	 const	{ return texList[id].nHeight; }
	// TODO: Check for DEBUG out of bounds check
	int Textures::getTextureWidth(const int id) const		{ return texList[id].nWidth; }
}