/*!
 * \file Shaders.cpp
 *
 * \author Sam Rivera
 * \date 9/27/2015
 *
 * 
 */
#include "Shaders.h"

using namespace GFXCore;

int Shaders::nIdGenerator = -1;

Shaders::Shaders() :
pFxPool(NULL),
hViewProj(NULL),
hView(NULL),
hWorld(NULL),
hWVP(NULL),
hWIT(NULL),
hEye(NULL),
hLightDir(NULL),
hLightDiffuse(NULL),
hLightAmbient(NULL),
hLightSpecular(NULL),
hLightPos(NULL),
hMtrlDiffuse(NULL),
hMtrlAmbient(NULL),
hMtrlSpecular(NULL),
hSpecularExp(NULL),
hTexDiffuse(NULL)
{
}


Shaders::~Shaders()
{
}

bool GFXCore::Shaders::init(const int numStartShaders)
{
	shaderList.reserve(numStartShaders);
	return createFxPool();
}

int GFXCore::Shaders::loadShader(IDirect3DDevice9* device, const wchar_t* fileName, const char* techName, const char* worldMatName)
{
	for (unsigned int i = 0; shaderList.size(); ++i)
		if (0 == wcscmp(fileName, shaderList[i].strFileName))
			return i;

	ShaderData		data;
	ID3DXBuffer* err = NULL;
	memset(&data, NULL, sizeof(ShaderData));	
	wcscpy_s(data.strFileName, fileName);

	HR(D3DXCreateEffectFromFile(device, data.strFileName, NULL, NULL,
											  D3DXFX_NOT_CLONEABLE | D3DXFX_LARGEADDRESSAWARE,
											  pFxPool, &data.pFx, &err));

	if (err) {
		ErrorMsg(L"Create Effect Failure!", L"Shader::loadShader()");
		ReleaseCom(err);
		return -1;
	}
	ReleaseCom(err);

	data.hTech = data.pFx->GetTechniqueByName(techName);
	data.hWorld = data.pFx->GetTechniqueByName(worldMatName);

	if (shaderList.empty()) {
		hLightDiffuse		= data.pFx->GetParameterByName(0, "gLightDiffuse");
		hLightAmbient		= data.pFx->GetParameterByName(0, "gLightAmbient");
		hLightDir			= data.pFx->GetParameterByName(0, "gLightDir");
		hViewProj			= data.pFx->GetParameterByName(0, "gViewProj");
		hTexDiffuse			= data.pFx->GetParameterByName(0, "gTexDiffuse");
		hMtrlAmbient		= data.pFx->GetParameterByName(0, "gMtrlAmbientColor");
		hMtrlDiffuse		= data.pFx->GetParameterByName(0, "gMtrlDiffuseColor");
		hMtrlSpecular		= data.pFx->GetParameterByName(0, "gMtrlSpecularColor");
		hSpecularExp		= data.pFx->GetParameterByName(0, "gSpecularExp");
		hView				= data.pFx->GetParameterByName(0, "gView");
		hWorld				= data.pFx->GetParameterByName(0, "gWorld");
		hWVP				= data.pFx->GetParameterByName(0, "gWVP");
		hEye					= data.pFx->GetParameterByName(0, "gEye");
		hLightPos			= data.pFx->GetParameterByName(0, "gLightPos");
		hLightSpecular	= data.pFx->GetParameterByName(0, "gLightSpecular");
		hWIT					= data.pFx->GetParameterByName(0, "gWIT");
	}

	shaderList.push_back(data);
	return ++nIdGenerator;
}

bool GFXCore::Shaders::createFxPool()
{
	if (FAILED(D3DXCreateEffectPool(&pFxPool))) {
		ErrorMsg(L"Create Effect Pool Failure!", L"Shaders::createFxPool()");
		return false;
	}

	return true;
}

void GFXCore::Shaders::setShaderVarWorldMat(const int id, const D3DXMATRIX& world)
{
#if defined (_DEBUG) | defined(DEBUG)
	CHECK_OUT_OF_BOUNDS(id, (int)shaderList.size());
#endif

	HR(shaderList[id].pFx->SetMatrix(shaderList[id].hWorld, &world));
}

void GFXCore::Shaders::shutdown()
{
	ReleaseCom(pFxPool);

	for (unsigned int i = 0; i < shaderList.size(); ++i) 
		if (shaderList[i].pFx)
			ReleaseCom(shaderList[i].pFx);
	
	shaderList.clear();
	shaderList.resize(0);
}

int GFXCore::Shaders::getNumShadersLoaded()
{
	return shaderList.size();
}

void GFXCore::Shaders::setMtrlAmbient(const D3DXVECTOR4& c)
{
	HR(shaderList[0].pFx->SetVector(hMtrlAmbient, &c));
}

void GFXCore::Shaders::setMtrlDiffuse(const D3DXVECTOR4& c)
{
	HR(shaderList[0].pFx->SetVector(hMtrlDiffuse, &c));
}

void GFXCore::Shaders::setMtrlSpecular(const D3DXVECTOR4& c)
{
	HR(shaderList[0].pFx->SetVector(hMtrlSpecular, &c));
}

void GFXCore::Shaders::setLightDir(const D3DXVECTOR4& v)
{
	HR(shaderList[0].pFx->SetVector(hLightDir, &v));
}

void GFXCore::Shaders::setLightDiffuse(const D3DXVECTOR4& c)
{
	HR(shaderList[0].pFx->SetVector(hLightDiffuse, &c));

}

void Shaders::setLightAmbient(const D3DXVECTOR4& c)
{
	HR(shaderList[0].pFx->SetVector(hLightAmbient, &c));
}

void Shaders::setSpecularExp(const float s)
{
	HR(shaderList[0].pFx->SetFloat(hSpecularExp, s));
}

void Shaders::setViewProj(const D3DXMATRIX& vp)
{
	HR(shaderList[0].pFx->SetMatrix(hViewProj, &vp));
}

void Shaders::setEye(const D3DXVECTOR4& pos)
{
	HR(shaderList[0].pFx->SetVector(hEye, &pos));
}

void Shaders::setWVP(const D3DXMATRIX& wvp)
{
	HR(shaderList[0].pFx->SetMatrix(hWVP, &wvp));
}

void Shaders::setView(const D3DXMATRIX& view)
{
	HR(shaderList[0].pFx->SetMatrix(hView, &view));
}

void Shaders::setWorld(const D3DXMATRIX& world)
{
	HR(shaderList[0].pFx->SetMatrix(hWorld, &world));
}

void Shaders::setLightPos(const D3DXVECTOR4& v)
{
	HR(shaderList[0].pFx->SetVector(hLightPos, &v));
}

void Shaders::setLightSpecular(const D3DXVECTOR4& c)
{
	HR(shaderList[0].pFx->SetVector(hLightSpecular, &c));
}

void Shaders::setWIT(const D3DXMATRIX& wit)
{
	HR(shaderList[0].pFx->SetMatrix(hWIT, &wit));
}
