#ifndef  _FONT_H_
#define _FONT_H_

#include "SDL.h" 
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "checkML.h"
#include "SDLError.h"

#include <string>

class Font
{
private:
	TTF_Font* font_;

	void clean();

public:
	Font() : font_(nullptr) {}
	~Font();

	void load(std::string filename, int size);
	SDL_Surface* generateSurface(std::string text, SDL_Color color) const;
	// Calcula cuanto ocupa un string s
	int getSizeOfText(std::string s, int& w, int& h);
};

#endif // ! _FONT_H_