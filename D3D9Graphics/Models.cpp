#include "Models.h"
#include "Textures.h"
#include "Vertex.h"

using namespace GFXCore;
using std::vector;

int Models::nIdGenerator = -1;

Models::Models()
{
}


Models::~Models()
{
}

bool GFXCore::Models::init(const int startNumModels /*= 10*/)
{
	modelList.reserve(startNumModels);

	return true;
}

int Models::loadModel(IDirect3DDevice9* device, const wchar_t* fileName,  
								Textures& textures,
								const D3DXVECTOR3& initPos, 
								const D3DXVECTOR3& initRot, 
								const D3DXVECTOR3& initScale, 
								DWORD options)
{
	for (unsigned int i = 0; i < modelList.size(); ++i) 
		if (0 == wcscmp(fileName, modelList[i].strFileName))
			return i;

	XModelData modelData;
	memset(&modelData, NULL, sizeof(XModelData));
	wcscpy_s(modelData.strFileName, MAX_FILE_NAME, fileName);

	if (FAILED(D3DXLoadMeshFromX(modelData.strFileName, options, device, &modelData.pAdjacency,
													  &modelData.pMaterials, &modelData.pEffectInstances,
													  &modelData.dwNumMaterials, &modelData.pMesh))) {

		ErrorMsg(L"Load Mesh failure - Models::loadModel().", fileName);

		return -1;

	}

	D3DXMATERIAL* modelMats = (D3DXMATERIAL*)modelData.pMaterials->GetBufferPointer();
	if (NULL == modelMats)
		return -1;

 	modelData.materialList.reserve(modelData.dwNumMaterials);
 	modelData.textureList.reserve(modelData.dwNumMaterials);

	for (DWORD i = 0; i < modelData.dwNumMaterials; ++i) {
		modelData.materialList.push_back(modelMats[i].MatD3D);
		modelData.materialList[i].Ambient = modelData.materialList[i].Diffuse;//D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // TODO: change this to a func param

		if (modelMats[i].pTextureFilename) {
			int len = 0;
			wchar_t wstr[MAX_FILE_NAME] = L"";
			// TODO: change this to actual directory when all cores combined
			char append[MAX_FILE_NAME] = "..\\GraphicsCoreTests\\Assets\\";
			strcat_s(append, modelMats[i].pTextureFilename);
			mbstowcs(wstr, append, MAX_FILE_NAME);
			int texId = textures.loadTexture(device, wstr);
			modelData.textureList.push_back(texId);
		}
	}

	D3DXMatrixIdentity(&modelData.translationMat);
	D3DXMatrixIdentity(&modelData.rotationMat);
	D3DXMatrixIdentity(&modelData.scalingMat);
	D3DXMatrixIdentity(&modelData.worldTranformMat);

	D3DXMatrixTranslation(&modelData.translationMat, initPos.x, initPos.y, initPos.z);
	D3DXMatrixRotationYawPitchRoll(&modelData.rotationMat, initRot.x, initRot.y, initRot.z);
	D3DXMatrixScaling(&modelData.scalingMat, initScale.x, initScale.y, initScale.z);

	D3DXMatrixMultiply(&modelData.scalingMat, &modelData.scalingMat, &modelData.rotationMat);
	D3DXMatrixMultiply(&modelData.worldTranformMat, &modelData.scalingMat, &modelData.translationMat);
	// TODO: add functionality to be able to set a particular shader to the model
	modelList.push_back(modelData);
	return ++nIdGenerator;
}

void Models::update(const int id, const D3DXVECTOR3& position, 
											const bool rotChange, const bool scaleChange,
											const D3DXVECTOR3& rotation, 
											const D3DXVECTOR3& scaling)
{
#if defined (_DEBUG) | defined(DEBUG)
	CHECK_OUT_OF_BOUNDS(id, (int)modelList.size());
#endif

	setTranslation(id, position);
	if (rotChange)
		setRotation(id, rotation);
	if (scaleChange)
		setScaling(id, scaling);

	D3DXMatrixMultiply(&modelList[id].scalingMat, &modelList[id].scalingMat, &modelList[id].rotationMat);
	D3DXMatrixMultiply(&modelList[id].worldTranformMat, &modelList[id].scalingMat, &modelList[id].translationMat);
}

void Models::render(IDirect3DDevice9* device, Textures& textures, const int id)
{
#if defined (_DEBUG) | defined(DEBUG)
	CHECK_OUT_OF_BOUNDS(id, (int)modelList.size());
#endif

	HR(device->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
	HR(device->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
	HR(device->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR));
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
	device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(255, 255, 255, 0));
	device->SetTransform(D3DTS_WORLD, &modelList[id].worldTranformMat);
	device->SetMaterial(&modelList[id].materialList[0]);
	device->SetTexture(0, textures.getTexture(modelList[id].textureList[0]));
	modelList[id].pMesh->DrawSubset(0);
}

void Models::shutdown()
{
	for (unsigned int i = 0; i < modelList.size(); ++i) {
		if (modelList[i].pAdjacency)
			ReleaseCom(modelList[i].pAdjacency);
		if (modelList[i].pEffectInstances)
			ReleaseCom(modelList[i].pEffectInstances);
		if (modelList[i].pMaterials)
			ReleaseCom(modelList[i].pMaterials);
		if (modelList[i].pMesh)
			ReleaseCom(modelList[i].pMesh);

		modelList[i].materialList.clear();
		modelList[i].materialList.resize(0);

		modelList[i].textureList.clear();
		modelList[i].textureList.resize(0);
	}
}

