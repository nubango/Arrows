#ifndef _MAINMENUSTATE_H_
#define _MAINMENUSTATE_H_

#include "checkML.h"
#include "GameState.h"
#include "MenuButton.h"

class SDLApp;

class MainMenuState :
	public GameState
{
public:
	MainMenuState() : GameState() {}
	MainMenuState(SDLApp* app);
	virtual ~MainMenuState();

	virtual void render() const;
	virtual void update();
	virtual void handleEvent(SDL_Event& e);

	virtual std::string getStateName() { return "MainMenu"; }
};

#endif // !_MAINMENUSTATE_H_