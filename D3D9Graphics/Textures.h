#pragma once
#include <vector>
#include "D3DUtils.h"

using std::vector;

namespace GFXCore
{
	struct TexureData {
		wchar_t		strFileName[256];
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
		inline int getTextureWidth(const int id);
		inline int getTextureHeight(const int id);

		Textures();
		~Textures();

	protected:
		vector<TexureData>	texList;

	private:
		static int nIdGenerator;
	};


	IDirect3DTexture9* GFXCore::Textures::getTexture(const int id)	{ return texList[id].pTex; }
	int Textures::getTextureHeight(const int id)		{ return texList[id].nHeight; }
	int Textures::getTextureWidth(const int id)		{ return texList[id].nWidth; }
}