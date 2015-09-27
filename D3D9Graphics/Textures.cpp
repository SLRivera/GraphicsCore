/*!
 * \file Textures.cpp
 *
 * \author Sam Rivera
 * \date 9/27/2015
 *
 * 
 */
#include "Textures.h"

using namespace GFXCore;

int Textures::nIdGenerator = -1;

Textures::Textures()
{
}


Textures::~Textures()
{
}

bool GFXCore::Textures::init(const int startNumTex)
{
	texList.reserve(startNumTex);

	return true;
}

int Textures::loadTexture(IDirect3DDevice9* device, const wchar_t* fileName)
{
	for (unsigned int i = 0; i < texList.size(); ++i)
		if (0 == wcscmp(fileName, texList[i].strFileName))
			return i;

	TexureData tex;
	memset(&tex, NULL, sizeof(TexureData));
	wcscpy_s(tex.strFileName, MAX_FILE_NAME, fileName);

	D3DXIMAGE_INFO texInfo;
	memset(&texInfo, NULL, sizeof(D3DXIMAGE_INFO));

	HR(D3DXGetImageInfoFromFile(tex.strFileName, &texInfo));
	tex.nHeight = texInfo.Height;
	tex.nWidth = texInfo.Width; 
	
	if (FAILED(D3DXCreateTextureFromFile(device, tex.strFileName, &tex.pTex))) {
		ErrorMsg(L"Create Texture Failure.", fileName);
		return -1;
	}
	
	texList.push_back(tex);
	return ++nIdGenerator;
}

void Textures::shutdown()
{
	for (unsigned int i = 0; i < texList.size(); ++i){
		if (texList[i].pTex)
			ReleaseCom(texList[i].pTex);
	}

	texList.clear();
	texList.resize(0);
}
