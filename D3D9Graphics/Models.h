#pragma once
#include <vector>
#include "D3DUtils.h"
#include "Textures.h"


namespace GFXCore
{
	struct XModelData {
		vector<D3DMATERIAL9>	materialList;
		vector<int>		textureList;
		D3DXMATRIX		translationMat;
		D3DXMATRIX		rotationMat;
		D3DXMATRIX		scalingMat;
		D3DXMATRIX		worldTranformMat;
		ID3DXMesh*		pMesh;
		ID3DXBuffer*		pAdjacency;
		ID3DXBuffer*		pMaterials;
		ID3DXBuffer*		pEffectInstances;
		DWORD				dwNumMaterials;
		wchar_t				strFileName[MAX_FILE_NAME];
		int						nShaderId;
	};

	class Models
	{
	public:
		bool init(const int startNumModels = 10);
		int loadModel(IDirect3DDevice9* device, const wchar_t* fileName, 
							Textures& textures,
							const D3DXVECTOR3& initPos, 
							const D3DXVECTOR3& initRot, 
							const D3DXVECTOR3& initScale, 
							DWORD options);
		void update(const int id, const D3DXVECTOR3& position, 
						  const bool rotChange, const bool scaleChange,
						  const D3DXVECTOR3& rotation, 
						  const D3DXVECTOR3& scaling);
		void render(IDirect3DDevice9* device, Textures& textures, const int id);
		void shutdown();

		inline void setTranslation(const int id, const D3DXVECTOR3& newPos);
		inline void setRotation(const int id, const D3DXVECTOR3& newRot);
		inline void setScaling(const int id, const D3DXVECTOR3& newScale);
		inline const XModelData& getModelData(const int id);
		inline const int getNumModels()	{ return modelList.size(); }

		Models();
		~Models();

	protected:
		std::vector<XModelData>	modelList;

	private:
		static int	nIdGenerator;
		
	};

	void Models::setTranslation(const int id, const D3DXVECTOR3& newPos)
	{
		D3DXMatrixIdentity(&modelList[id].translationMat);
		D3DXMatrixTranslation(&modelList[id].translationMat, newPos.x, newPos.y, newPos.z);
	}

	void Models::setRotation(const int id, const D3DXVECTOR3& newRot)
	{
		D3DXMatrixIdentity(&modelList[id].rotationMat);
		D3DXMatrixRotationYawPitchRoll(&modelList[id].rotationMat, newRot.y, newRot.x, newRot.z);
	}

	void Models::setScaling(const int id, const D3DXVECTOR3& newScale)
	{
		D3DXMatrixIdentity(&modelList[id].scalingMat);
		D3DXMatrixScaling(&modelList[id].scalingMat, newScale.x, newScale.y, newScale.z);
	}

	const XModelData& Models::getModelData(const int id) 	{ return modelList[id]; }
}