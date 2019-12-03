#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "checkML.h"
#include "GameState.h"

class PlayState :
	public GameState
{
private:
	// std::list<Arrow*> arrows_;
	std::list<GameObject*> objectsToErase_;

public:
	void update();
	void handleEvent(SDL_Event& e);
};

#endif // !_PLAYSTATE_H_