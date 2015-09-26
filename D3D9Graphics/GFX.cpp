#include "GFX.h"

using namespace GFXCore;

Graphics* Graphics::pInstance = NULL;


GFXCore::Graphics::Graphics() :
nModelListIndex(0),
nSpriteListIndex(0),
nTextListIndex(0)
{
	d3d = D3DCore::get(); 	
	modelRenderList.resize(100);
	spriteRenderList.resize(25);
	textRenderList.resize(10);
}

void GFXCore::Graphics::shutdown()
{
	destroyAllVertexDeclarations();
	textures.shutdown();
	models.shutdown();
	text.shutdown();
	sprites.shutdow();
	shaders.shutdown();
	d3d->shutdown();
	del();
}

bool GFXCore::Graphics::initModules(const int numStartTexs /*= 20*/, const int numStartModels /*= 10*/, const int numStartFonts /*= 5*/, const int numStartSprites /*= 15*/, const int numStartShaders /*= 4*/)
{
	bool res = true;

	res &= textures.init(numStartTexs);
	res &= text.init(numStartFonts);
	res &= models.init(numStartModels);
	res &= sprites.init(d3d->getDevice(), numStartSprites);
	res &= shaders.init(numStartShaders);

	initAllVertexDeclarations();

	return res;
}

int GFXCore::Graphics::loadFont(const FontData& fontData)
{
	return text.createFont(d3d->getDevice(), fontData);
}

int GFXCore::Graphics::loadModel(const wchar_t* fileName, const D3DXVECTOR3& initPos /*= D3DXVECTOR3(0.0f, 0.0f, 0.0f)*/, 
												const D3DXVECTOR3& initRot /*= D3DXVECTOR3(0.0f, 0.0f, 0.0f)*/, 
												const D3DXVECTOR3& initScale /*= D3DXVECTOR3(1.0f, 1.0f, 1.0f)*/, 
												DWORD options /*= D3DXMESH_MANAGED*/)
{
	return models.loadModel(d3d->getDevice(), fileName, textures, initPos, initRot, initScale, options);
}

int GFXCore::Graphics::loadTexture(const wchar_t* fileName)
{
	return textures.loadTexture(d3d->getDevice(), fileName);
}

bool GFXCore::Graphics::initGFX(const HINSTANCE hInst, const wchar_t* wndCaption, const int width /*= 1024*/, const int height /*= 768*/, const D3DDEVTYPE requestedDevtype /*= D3DDEVTYPE_HAL*/, const DWORD requestedVP /*= D3DCREATE_HARDWARE_VERTEXPROCESSING*/)
{
	return d3d->initGfxCore(hInst, wndCaption, width, height, requestedDevtype, requestedVP);
}

int GFXCore::Graphics::loadSprite(const wchar_t* fileName, const bool centerIsTopLeft, const D3DXVECTOR3& initPos /*= D3DXVECTOR3(0.0f, 0.0f, 0.0f)*/, D3DCOLOR initColor /*= D3DCOLOR_RGBA(255, 255, 255, 255)*/, RECT* clipRect /*= NULL*/)
{
	return sprites.loadSprite(d3d->getDevice(), fileName, textures, initPos, centerIsTopLeft, initColor, clipRect);
}

void GFXCore::Graphics::updateModel(const int id, const D3DXVECTOR3& position, const bool rotChange /*= false*/, const bool scaleChange /*= false*/, const D3DXVECTOR3& rotation /*= D3DXVECTOR3(0.0f, 0.0f, 0.0f)*/, const D3DXVECTOR3& scaling /*= D3DXVECTOR3(1.0f, 1.0f, 1.0f)*/)
{
	models.update(id, position, rotChange, scaleChange, rotation, scaling);
}

void GFXCore::Graphics::updateSprite(const int id, const D3DXVECTOR3& position)
{
	sprites.update(id, position);
}

int GFXCore::Graphics::loadShader(const wchar_t* fileName, const char* techName, const char* worldMatName)
{
	return shaders.loadShader(d3d->getDevice(), fileName, techName, worldMatName);
}

void GFXCore::Graphics::cameraSetLens(const int width, const int height, const float nearZ, const float farZ)
{
	camera.setOrthoLens(d3d->getDevice(), width, height, nearZ, farZ);
}

void GFXCore::Graphics::updateCamera(const float dt)
{
	camera.update(dt, 0.0f);
}

int GFXCore::Graphics::windowWidth() const
{
	return d3d->getWndWidth();
}

int GFXCore::Graphics::windowHeight() const
{
	return d3d->getWndHeight();
}

HINSTANCE GFXCore::Graphics::getAppInstance() const
{
	return d3d->getAppInstance();
}

HWND GFXCore::Graphics::getHWND() const
{
	return d3d->getHWND();
}

void GFXCore::Graphics::onLostDevice()
{
	d3d->onLostDevice();
	sprites.onLostDevice();
	text.onLostDevice();
}

void GFXCore::Graphics::onResetDevice()
{
	d3d->onResetDevice();
	sprites.onResetDevice();
	text.onResetDevice();
}

bool GFXCore::Graphics::isDeviceLost()
{
	return d3d->isDeviceLost();
}

void GFXCore::Graphics::addToModelRenderList(const GSP420::ABC* obj)
{
#if defined DEBUG | _DEBUG
	if (NULL == obj) {
		ErrorMsg(L"Passing NULL", L"Graphics::addToModelRenderList()");
		return;
	}
#endif

	if ((unsigned int)nModelListIndex + 1 < modelRenderList.size()) {
		modelRenderList[nModelListIndex] = obj;
		++nModelListIndex;
	}
	else {
		modelRenderList.push_back(obj);
		++nModelListIndex;
	}
}

void GFXCore::Graphics::addToSpriteRenderList(const int* idsToRender, const int count)
{
#if defined DEBUG | _DEBUG
	if (NULL == idsToRender) {
		ErrorMsg(L"Passing NULL", L"Graphics::addToSpriteRenderList()");
		return;
	}
#endif

	if (count >= (signed)spriteRenderList.size())
		spriteRenderList.resize(spriteRenderList.size() * 2);

	for (int i = 0; i < count; ++i) {
		spriteRenderList[i] = idsToRender[i];
	}

	nSpriteListIndex = count;
}

void GFXCore::Graphics::addToTextRenderList(const int* idsToRender, const int count)
{
#if defined DEBUG | _DEBUG
	if (NULL == idsToRender) {
		ErrorMsg(L"Passing NULL", L"Graphics::addToTextRenderList()");
		return;
	}
#endif
	if (count >= (signed)textRenderList.size())
		textRenderList.resize(textRenderList.size() * 2);

	for (int i = 0; i < count; ++i) {
		textRenderList[i] = idsToRender[i];
	}

	nTextListIndex = count;
}

void GFXCore::Graphics::renderScene()
{
	d3d->beginScene(D3DCOLOR_XRGB(0, 0, 100));

	for (int i = 0; i < nModelListIndex; ++i) {
 		models.update(modelRenderList[i]->getModelId(),
 							  modelRenderList[i]->getPosition(),
 							  true, true,
 							  modelRenderList[i]->getFixedRotation(), 
 							  modelRenderList[i]->getScale());
		models.render(d3d->getDevice(), textures, modelRenderList[i]->getModelId());
	}

	sprites.beginDraw();
	for (int i = 0; i < nSpriteListIndex; ++i) 
		sprites.render(spriteRenderList[i], textures);
	sprites.endDraw();

	for (int i = 0; i < nTextListIndex; ++i)
		text.render(textRenderList[i]);

	d3d->endScene();

	nModelListIndex = 0;
	nSpriteListIndex = 0;
	nTextListIndex = 0;
}

void GFXCore::Graphics::setTextForFont(const int fontId, const wchar_t* newText)
{
	text.setText(fontId, newText);
}

int GFXCore::Graphics::getTextureWidth(const int id)
{
	return textures.getTextureWidth(id);
}

int GFXCore::Graphics::getTextureHeight(const int id)
{
	return textures.getTextureHeight(id);
}

int GFXCore::Graphics::getSpriteWidth(const int id)
{
	return textures.getTextureWidth(sprites.getSprite(id).nTextureId);
}

int GFXCore::Graphics::getSpriteHeight(const int id)
{
	return textures.getTextureHeight(sprites.getSprite(id).nTextureId);

}

