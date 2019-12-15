#ifndef  _FONT_H_
#define _FONT_H_

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "SDL_ttf.h"
#include "checkML.h"
#include "SDLError.h"

#include <string>

class Font
{
private:
	TTF_Font* font_;
	int size_;

	void clean();

public:
	Font() : font_(nullptr), size_(0) {}
	Font(std::string filename, int size);
	~Font();

	bool load(std::string filename, int size);
	SDL_Surface* generateSurface(std::string text, SDL_Color color) const;

};

#endif // ! _FONT_H_