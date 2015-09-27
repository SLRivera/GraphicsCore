/*!
* \file Shaders.h
*
* \author Sam Rivera
* \date September 2015
*
* Last Revision: 9/23/15
*/
#pragma once
#include <vector>
#include "D3DUtils.h"

namespace GFXCore
{
	struct ShaderData {
		wchar_t			strFileName[MAX_FILE_NAME];
		ID3DXEffect*	pFx;
		D3DXHANDLE	hTech;
		D3DXHANDLE	hWorld;
	};

	class Shaders
	{
	public:
		bool init(const int numStartShaders);
		int loadShader(IDirect3DDevice9* device, const wchar_t* fileName, const char* techName, const char* worldMatName);
		void shutdown();
		void setShaderVarWorldMat(const int id, const D3DXMATRIX& world);
		int	 getNumShadersLoaded();
		inline ShaderData& getShader(const int id);

		void setMtrlAmbient(const D3DXVECTOR4& c);
		void setMtrlDiffuse(const D3DXVECTOR4& c);
		void setMtrlSpecular(const D3DXVECTOR4& c);
		void setLightDir(const D3DXVECTOR4& v);
		void setLightDiffuse(const D3DXVECTOR4& c);
		void setLightAmbient(const D3DXVECTOR4& c);
		void setLightSpecular(const D3DXVECTOR4& c);
		void setLightPos(const D3DXVECTOR4& v);
		void setSpecularExp(const float s);
		void setViewProj(const D3DXMATRIX& vp);
		void setEye(const D3DXVECTOR4& pos);
		void setWVP(const D3DXMATRIX& wvp);
		void setView(const D3DXMATRIX& view);
		void setWorld(const D3DXMATRIX& world);
		void setWIT(const D3DXMATRIX& wit);

		Shaders();
		~Shaders();

	protected:
		bool createFxPool();

		std::vector<ShaderData>		shaderList;
		ID3DXEffectPool*	pFxPool;

		D3DXHANDLE		hViewProj,
								hView,
								hWorld,
								hWVP,
								hWIT,
								hEye,
								hLightDir,
								hLightDiffuse,
								hLightAmbient,
								hLightSpecular,
								hLightPos,
								hMtrlDiffuse,
								hMtrlAmbient,
								hMtrlSpecular,
								hSpecularExp,
								hTexDiffuse;

	private:
		static int nIdGenerator;
	};

	ShaderData& Shaders::getShader(const int id)		{ return shaderList[id]; }
}