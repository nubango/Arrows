#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "checkML.h"
#include "GameState.h"

#include <time.h>

class SDLApp;

class PlayState :
	public GameState
{
private:
	// std::list<Arrow*> arrows_;
	// std::list<GameObject*> objectsToErase_;

public:
	PlayState() : GameState() {}
	PlayState(SDLApp* app) :GameState(app) {}
	virtual ~PlayState() {}

	virtual void update();
	virtual void render() const;
	virtual void handleEvent(SDL_Event& e);

	virtual StateName getStateName() { return StateName::PLAY_STATE; }
};

#endif // !_PLAYSTATE_H_