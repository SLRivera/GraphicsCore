/*!
 * \file GFX.h
 *
 * \author Sam Rivera
 * \date September 2015
 *
 * Last Revision: 9/23/15
 */
#pragma once
#include <list>
#include "D3DCore.h"
#include "Textures.h"
#include "Models.h"
#include "Camera.h"
#include "Text.h"
#include "Sprites.h"
#include "ABC.h"
#include "Shaders.h"
#include "Vertex.h"
// TODO: remove later
#include "DirectInput.h"
// TODO: Change to proper directory once integration begins
#pragma comment (lib, "E:\\School Materials\\GSP420\\Week 3\\GraphicsCore\\Debug\\D3D9GraphicsD.lib")

#define GFX		GFXCore::Graphics::get()
/*!
 * \class GFXCore::Graphics
 *
 *
 * This singleton class is the interface for all the classes required in order to have a graphics working
 * for a successful engine in order to render. It holds functionality for the loading of the 
 * following: Models, Textures, Sprites, Shaders, Fonts. In order to access data that has been 
 * loaded, the user most capture the integer returned by each of the load functions. The
 * user then uses the captured integer and passes it into the functions that manipulate 
 * or otherwise use the data that has been loaded. 
 *
 *	Use the macro, GFX, in order to access this interface class.
 *
 *
 * \author Sam Rivera
 *
 * \version 1.0
 *
 * \date September 2015
 *
 * Contact: theebola8me@gmail.com
 *
 */
namespace GFXCore
{
	class Graphics
	{
	public:
		//************************************
		// Method:    initGFX
		// FullName:  GFXCore::Graphics::initGFX
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: const HINSTANCE hInst - the instance of the application
		// Parameter: const wchar_t * wndCaption - the window's caption
		// Parameter: const int width - the width of the window
		// Parameter: const int height - the height of the window
		// Parameter: const D3DDEVTYPE requestedDevtype - the requested device type
		// Parameter: const DWORD requestedVP - the requested vertex processing
		// Notes: This function initializes Windows and DirectX
		//************************************
		bool initGFX(const HINSTANCE hInst, const wchar_t* wndCaption,
						  const int width = WINDOW_WIDTH, const int height = WINDOW_HEIGHT,
						  const D3DDEVTYPE requestedDevtype = D3DDEVTYPE_HAL,
						  const DWORD requestedVP = D3DCREATE_HARDWARE_VERTEXPROCESSING);

		//************************************
		// Method:    initComponents
		// FullName:  GFXCore::Graphics::initComponents
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const int numStartTexs - preset the number of nodes for textures
		// Parameter: const int numStartModels - preset the number of nodes for models
		// Parameter: const int numStartFonts - preset the number of nodes for fonts
		// Parameter: const int numStartSprites - preset the number of nodes for sprites
		// Parameter: const int numStartShaders - preset the number of nodes for shaders
		// Notes: This function cannot be called before initGFX(). Call this function before adding
		//			any objects to preset the size of the vectors used to store the data and init
		//			individual modules. 
		//************************************
		bool initModules(const int numStartTexs = 20, const int numStartModels = 10, const int numStartFonts = 5, const int numStartSprites = 15, const int numStartShaders = 4);

		//************************************
		// Method:    onLostDevice
		// FullName:  GFXCore::Graphics::onLostDevice
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Notes: Call this function after the system lost access to the device
		//************************************
		void onLostDevice();

		//************************************
		// Method:    onResetDevice
		// FullName:  GFXCore::Graphics::onResetDevice
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Notes: Call this function to reset the device after it has been lost
		//************************************
		void onResetDevice();

		//************************************
		// Method:    isDeviceLost
		// FullName:  GFXCore::Graphics::isDeviceLost
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Notes: Call at the beginning of each frame to determine if we still have access to the 
		//			 graphics card
		//************************************
		bool isDeviceLost();

		//************************************
		// Method:    shutdown
		// FullName:  GFXCore::Graphics::shutdown
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Notes: Call this function before the application ends
		//			Calls Release on all COM objects
		//************************************
		void shutdown();

		//************************************
		// Method:    loadTexture
		// FullName:  GFXCore::Graphics::loadTexture
		// Access:    public 
		// Returns:   int - capture this integer in order to access the texture later on
		// Qualifier:
		// Parameter: const wchar_t * fileName - the texture's file name
		// Notes: Use this function to load a texture
		//				Capture the returned int so that you can access the texture 
		//				after loading
		//************************************
		int loadTexture(const wchar_t* fileName);
		int getTextureWidth(const int id);	// TODO: might make private
		int getTextureHeight(const int id); // TODO: might make private

		//************************************
		// Method:    loadModel
		// FullName:  GFXCore::Graphics::loadModel
		// Access:    public 
		// Returns:   int - capture this integer in order to access the model later on
		// Qualifier:
		// Parameter: const wchar_t * fileName - the filename of the X model 
		// Parameter: const D3DXVECTOR3 & initPos - the initial position of the model
		// Parameter: const D3DXVECTOR3 & initRot - the initial rotation of the model
		// Parameter: const D3DXVECTOR3 & initScale - the initial scale of the model
		// Parameter: DWORD options - DirextX mesh options
		// Notes: Use this function to load an X model
		//				Capture the returned int so that you can access the model after loading
		//************************************
		int loadModel(const wchar_t* fileName, 
							const D3DXVECTOR3& initPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							const D3DXVECTOR3& initRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							const D3DXVECTOR3& initScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f),
							DWORD options = D3DXMESH_MANAGED);

		//************************************
		// Method:    loadFont
		// FullName:  GFXCore::Graphics::loadFont
		// Access:    public 
		// Returns:   int - capture this integer so you can access the font later on
		// Qualifier:
		// Parameter: const FontData & fontData - data structure used to hold the data 
		//															required to create a Font
		// Notes: Use this function to create a Font to be used later on for rendering text
		//			Capture the returned int in order to access the font after loading it
		//************************************
		int loadFont(const FontData& fontData);

		//************************************
		// Method:    setTextForFont
		// FullName:  GFXCore::Graphics::setTextForFont
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const int fontId - the ID of the font to set the string/text to display
		// Parameter: const wchar_t * newText - the string/text to display
		// Notes: Call this function after loading a font to set that font's text to display
		//************************************
		void setTextForFont(const int fontId, const wchar_t* newText);

		//************************************
		// Method:    loadShader
		// FullName:  GFXCore::Graphics::loadShader
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: const wchar_t * fileName
		// Parameter: const char * techName
		// Parameter: const char * worldMatName
		// Notes: NONE
		//************************************
		int loadShader(const wchar_t* fileName, const char* techName, const char* worldMatName);

		//************************************
		// Method:    updateModel
		// FullName:  GFXCore::Graphics::updateModel
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const int id
		// Parameter: const D3DXVECTOR3 & position
		// Parameter: const bool rotChange
		// Parameter: const bool scaleChange
		// Parameter: const D3DXVECTOR3 & rotation
		// Parameter: const D3DXVECTOR3 & scaling
		// Notes: NONE
		//************************************
		void updateModel(const int id, const D3DXVECTOR3& position,
								  const bool rotChange = false, const bool scaleChange = false,
								  const D3DXVECTOR3& rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								  const D3DXVECTOR3& scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f));

		//************************************
		// Method:    updateSprite
		// FullName:  GFXCore::Graphics::updateSprite
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const int id
		// Parameter: const D3DXVECTOR3 & position
		// Notes: NONE
		//************************************
		void updateSprite(const int id, const D3DXVECTOR3& position);

		//************************************
		// Method:    loadSprite
		// FullName:  GFXCore::Graphics::loadSprite
		// Access:    public 
		// Returns:   int -  capture this integer in order to reference the sprite after loading
		// Qualifier:
		// Parameter: const wchar_t * fileName - the filename of the sprite to load
		// Parameter: const bool centerIsTopLeft - set to false if you want the center to 
		//															be the center of the sprite instead of 
		//															the top left corner
		// Parameter: const D3DXVECTOR3 & initPos - the initial position of the sprite
		// Parameter: D3DCOLOR initColor - the initial color of the sprite
		// Parameter: RECT * clipRect - the clipping rectangle dimensions. Pass NULL if 
		//											the entire sprite is to be drawn
		// Notes: Use this function to load a sprite. Capture the returned int so that you can 
		//				access the sprite after loading it.
		//************************************
		int loadSprite(const wchar_t* fileName,
							const bool centerIsTopLeft = true,
							const D3DXVECTOR3& initPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DCOLOR initColor = D3DCOLOR_RGBA(255, 255, 255, 255),
							RECT* clipRect = NULL);
		int getSpriteWidth(const int id);
		int getSpriteHeight(const int id);

		//************************************
		// Method:    cameraSetLens
		// FullName:  GFXCore::Graphics::cameraSetLens
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const int width
		// Parameter: const int height
		// Parameter: const float nearZ
		// Parameter: const float farZ
		// Notes: NONE
		//************************************
		void cameraSetLens(const int width, const int height, const float nearZ, const float farZ);

		//************************************
		// Method:    renderScene
		// FullName:  GFXCore::Graphics::renderScene
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Notes: Call once per scene. Most populate each scene with calls to
		//  		 addToModelRenderList(), addToSpriteRenderList(), addToTextRenderList(). 
		//************************************
		void renderScene();

		//************************************
		// Method:    addToModelRenderList
		// FullName:  GFXCore::Graphics::addToModelRenderList
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const GSP420::ABC * obj - the object to be rendered
		// Notes: Call this function as you iterate through object lists to add them to the 
		//			  render list before rendering
		//************************************
		void addToModelRenderList(const GSP420::ABC* obj);

		//************************************
		// Method:    addToSpriteRenderList
		// FullName:  GFXCore::Graphics::addToSpriteRenderList
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const int * idsToRender - an array holding the captured ID for the loaded sprites you wish to render 
		// Parameter: const int count - the number of sprites to render
		// Notes: Call this function to add the ID's of the sprites that have been loaded to be rendered
		//************************************
		void addToSpriteRenderList(const int* idsToRender, const int count);

		//************************************
		// Method:    addToTextRenderList
		// FullName:  GFXCore::Graphics::addToTextRenderList
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const int * idsToRender - the ID's of the fonts/string you wish to render
		// Parameter: const int count - the number of fonts/strings to render
		// Notes: Call this function to add the ID's of the fonts/sprites that have been loaded to be rendered
		//************************************
		void addToTextRenderList(const int* idsToRender, const int count);
		
		//************************************
		// Method:    windowWidth
		// FullName:  GFXCore::Graphics::windowWidth
		// Access:    public 
		// Returns:   int - window's width
		// Qualifier: const
		// Notes: NONE
		//************************************
		int windowWidth() const;

		//************************************
		// Method:    windowHeight
		// FullName:  GFXCore::Graphics::windowHeight
		// Access:    public 
		// Returns:   int - window's height
		// Qualifier: const
		// Notes: NONE
		//************************************
		int windowHeight() const;

		//************************************
		// Method:    getAppInstance
		// FullName:  GFXCore::Graphics::getAppInstance
		// Access:    public 
		// Returns:   HINSTANCE - the instance handle of the application
		// Qualifier: const
		// Notes: accessor
		//************************************
		HINSTANCE getAppInstance() const;

		//************************************
		// Method:    getHWND
		// FullName:  GFXCore::Graphics::getHWND
		// Access:    public 
		// Returns:   HWND - the handle to the application's window
		// Qualifier: const
		// Notes: accessor
		//************************************
		HWND getHWND() const;

		static inline Graphics* get();

	protected:
		D3DCore*	d3d;
		Textures		textures;
		Models		models;
		Camera		camera;
		Text			text;
		Sprites		sprites;
		Shaders		shaders;

	private:
		std::vector<const GSP420::ABC*>		modelRenderList;
		std::vector<int>								spriteRenderList;
		std::vector<int>								textRenderList;

		static Graphics*	pInstance;

		int		nSpriteListIndex;
		int		nModelListIndex;
		int		nTextListIndex;

		static inline void del();
		void updateCamera(const float dt);

		Graphics();
		Graphics(const Graphics&);
		~Graphics() {}
	};
	
	Graphics* Graphics::get()	{
		if (NULL == pInstance) 
			pInstance = new Graphics;
		return pInstance;
	}
	void Graphics::del() {
		if (pInstance) {
			delete pInstance;
			pInstance = NULL;
		}
	}
}