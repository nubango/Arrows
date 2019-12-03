#ifndef _SDL_ERROR_H_
#define _SDL_ERROR_H_

#include "checkML.h"
#include "ArrowsError.h"

class SDLError : 
	public ArrowsError
{
public:
	SDLError(const std::string& msg) : ArrowsError(msg) {}
};

#endif // !_SDL_ERROR_H_