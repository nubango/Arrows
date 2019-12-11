#ifndef _PAUSESTATE_H_
#define _PAUSESTATE_H_

#include "checkML.h"
#include "GameState.h"
#include "MenuButton.h"

class SDLApp;

class PauseState :
	public GameState
{
public:
	PauseState() : GameState() {}
	PauseState(SDLApp* app);
	virtual ~PauseState();

	virtual void render() const;
	virtual void update();
	virtual void handleEvent(SDL_Event& e);

	virtual StateName getStateName() { return StateName::PAUSE_STATE; }
};

#endif // !_PAUSESTATE_H_