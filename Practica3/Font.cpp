#include "Font.h"

void Font::clean()
{
	if (font_)
	{
		TTF_CloseFont(font_);
		font_ = nullptr;
		size_ = 0;
	}
}

Font::Font(std::string filename, int size)
{
	load(filename, size);
}

Font::~Font()
{
	clean();
}

bool Font::load(std::string filename, int size)
{
	font_ = TTF_OpenFont(filename.c_str(), size);
	// ...
	return true;
}

SDL_Surface* Font::generateSurface(std::string text, SDL_Color color) const
{
	return TTF_RenderText_Solid(font_, text.c_str(), color);
}
