#ifndef _ENDSTATE_H_
#define _ENDSTATE_H_

#include "checkML.h"
#include "GameState.h"
#include "MenuButton.h"

class SDLApp;

class EndState :
	public GameState
{
private:
	bool win_;

public:
	EndState() : GameState(), win_(false) {}
	EndState(SDLApp* app);
	virtual ~EndState();

	virtual void render() const;
	virtual void update();
	virtual void handleEvent(SDL_Event& e);

	virtual StateName getStateName() { return StateName::END_STATE; }
};

#endif // !_ENDSTATE_H_