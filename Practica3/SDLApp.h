#ifndef _SDLAPP_H_
#define _SDLAPP_H_

#include "checkML.h"
#include "consts.h"
#include "SDL_image.h"
#include "SDL.h"
#include "SDLError.h"
#include "GameStateMachine.h"

class SDLApp
{
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	GameStateMachine* stateMachine_;

	bool exit_;

public:
	SDLApp();
	~SDLApp();

	void run();
	void render() const;
	void handleEvents();
};

#endif // !_SDLAPP_H_