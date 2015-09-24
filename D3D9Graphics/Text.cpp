#include "Text.h"

using namespace GFXCore;
using std::vector;

int Text::nIdGenerator = -1;

Text::Text()
{
}


Text::~Text()
{
}

int Text::createFont(IDirect3DDevice9* device, const FontData& textInfo)
{
// 	for (unsigned int i = 0; i < fontList.size(); ++i)
// 		if (0 == wcscmp(textInfo.strFontName, fontList[i].strFontName))
// 			return i;

 	FontData newFont;
 	memset(&newFont, NULL, sizeof(FontData));
	newFont = textInfo;
	
	if (FAILED(D3DXCreateFont(device, newFont.nFontHeight, newFont.nFontWidth, FW_NORMAL, 0, newFont.bItalics, DEFAULT_CHARSET,
										   OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
										   newFont.strFontName, &(newFont.pFont))))
		return -1;

	fontList.push_back(newFont);
	return ++nIdGenerator;
}

void GFXCore::Text::render(const int fontId)
{
#if defined (_DEBUG) | defined(DEBUG)
	CHECK_OUT_OF_BOUNDS(fontId, (int)fontList.size());
#endif

	HR(fontList[fontId].pFont->DrawTextW(NULL, fontList[fontId].strText, -1, &(fontList[fontId].textBoxDimens),
											DT_CENTER, fontList[fontId].textColor));
}

void Text::shutdown()
{
	for (unsigned int i = 0; i < fontList.size(); ++i) {
		if (fontList[i].pFont)
			ReleaseCom(fontList[i].pFont);
	}

	fontList.clear();
	fontList.resize(0);
}

bool GFXCore::Text::init(const int startNumFonts)
{
	fontList.reserve(startNumFonts);

	return true;
}
