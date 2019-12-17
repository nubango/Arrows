#include "Font.h"

void Font::clean()
{
	if (font_)
	{
		TTF_CloseFont(font_);
		font_ = nullptr;
	}
}

Font::~Font()
{
	clean();
}

void Font::load(std::string filename, int size)
{
	font_ = TTF_OpenFont(filename.c_str(), size);
}

SDL_Surface* Font::generateSurface(std::string text, SDL_Color color) const
{
	// Blended > Shaded > Solid 
	return TTF_RenderText_Blended(font_, text.c_str(), color);
}

int Font::getSizeOfText(std::string s, int& w, int& h)
{
	return TTF_SizeText(font_, s.c_str(), &w, &h);
}
