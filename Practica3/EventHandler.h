#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include "checkML.h"
#include "SDL.h"

#include <list>

class EventHandler
{
protected:
	std::list<EventHandler*>::iterator itHandler_;

public:
	EventHandler() {}
	virtual ~EventHandler() {}
	virtual bool handleEvent(SDL_Event& event) = 0;

	void setItHandler(const std::list<EventHandler*>::iterator& it) { itHandler_ = it; }
};

#endif // !_EVENTHANDLER_H_