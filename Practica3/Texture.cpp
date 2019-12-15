#include "Texture.h"

#include <iostream>

using namespace std;

void Texture::freeTexture() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

void Texture::load(string filename, int nRows, int nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (!tempSurface)
		throw SDLError("Error loading surface from " + filename + ". Error code: " + IMG_GetError());
	freeTexture();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!texture)
		throw SDLError("Error loading texture from " + filename + ". Error code: " + IMG_GetError());

	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

void Texture::loadFont(SDL_Renderer* renderer, std::string text, const Font& font, SDL_Color color)
{
	SDL_Surface* textSurface = font.generateSurface(text, color);
	if (textSurface == nullptr)
		;// throw exception("Unable to render text surface: " + TTF_GetError());
	else 
	{
		freeTexture();
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == nullptr) 
		{
			// throw exception("Unable to create texture from text: " + SDL_GetError());
			w = h = 0;
		}
		else 
		{
			w = textSurface->w;
			h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}
