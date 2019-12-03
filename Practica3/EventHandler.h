#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include "checkML.h"
#include "SDL_image.h"
#include "SDL.h"

#include <list>

class EventHandler
{
public:
	virtual bool handleEvent(SDL_Event& event) = 0;
};

#endif // !_EVENTHANDLER_H_