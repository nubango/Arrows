// Permite manejar texturas SDL

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "checkML.h"
#include "SDLError.h"

#include <string>

using namespace std;

class Texture {
private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	int w = 0;
	int h = 0;
	int fw = 0; // Frame width
	int fh = 0; // Frame height
	int numCols = 1;
	int numRows = 1;

public:
	Texture(SDL_Renderer* r) : renderer(r) {};
	Texture(SDL_Renderer* r, string filename, int numRows = 1, int numCols = 1) : renderer(r) { load(filename, numRows, numCols); };
	~Texture() { freeTexture(); };
	void freeTexture();

	int getW() const { return w; };
	int getH() const { return h; };
	int getNumCols() const { return numCols; };
	SDL_Texture* getTexture() const { return texture; };

	// Carga la textura de un fichero
	void load(string filename, int numRows = 1, int numCols = 1);
	// Dibuja la textura en la posicion proporcionada en su totalidad
	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	// Dibuja un frame de la textura en la posicion proporcionada
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

#endif // "__TEXTURE_H__
