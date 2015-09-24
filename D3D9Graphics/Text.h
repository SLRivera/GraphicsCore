#pragma once
#include <vector>
#include "D3DUtils.h"

namespace GFXCore
{
	struct FontData{
		RECT			textBoxDimens;
		wchar_t		strFontName[MAX_FILE_NAME];
		wchar_t		strText[MAX_FILE_NAME];
		D3DCOLOR	textColor;
		int		nFontHeight;
		int		nFontWidth;
		ID3DXFont* pFont;
		bool	bItalics;
	};

	class Text
	{
	public:
		bool init(const int startNumFonts);
		int createFont(IDirect3DDevice9* device, const FontData& textCreationInfo);
		void render(const int fontId);
		void shutdown();
		
		inline void onLostDevice();
		inline void onResetDevice();

		inline int getNumFonts();
//		inline FontData& getFont(const int fontId); // TODO: might remove and just create individual accessors
		inline void setText(const int fontId, const wchar_t* newText);

		Text();
		~Text();

	protected:
		std::vector<FontData>		fontList;

	private:
		static int	nIdGenerator;
	};

	int Text::getNumFonts()								{ return (int)fontList.size(); }
	//FontData& Text::getFont(const int fontId)		{ return fontList[fontId]; }
	
	inline void Text::setText(const int fontId, const wchar_t* newText)
	{
		wcscpy_s(fontList[fontId].strText, newText);
	}

	void Text::onLostDevice() {
		for (unsigned int i = 0; i < fontList.size(); ++i)
			HR(fontList[i].pFont->OnLostDevice());
	}

	void Text::onResetDevice() {
		for (unsigned int i = 0; i < fontList.size(); ++i)
			HR(fontList[i].pFont->OnResetDevice());
	}

}