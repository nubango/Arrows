#ifndef _MENUBUTTON_H_
#define _MENUBUTTON_H_

#include "checkML.h"
#include "SDLGameObject.h"
#include "EventHandler.h"
#include "SDLApp.h"
#include "Texture.h"

using CallBackOnClick = void(SDLApp * app);

class MenuButton :
	public SDLGameObject, public EventHandler
{
protected:
	SDLApp* app_;
	Texture* texture_;
	int x_, y_;
	int w_, h_;
	CallBackOnClick* cbOnClick_;

public:
	bool handleEvent(SDL_Event& e);

};

#endif // !_MENUBUTTON_H_