#include "PlayState.h"

#include "SDLApp.h"

void PlayState::update()
{
	/*
	for (auto itOb : objectsToErase_)
	{
		delete* itOb;
		itOb.erase();
	}

	objectsToErase_.clear();
	...

	if (...) levelPassed_ = true;

	if (levelPassed_)
	{
		if (levels == NUM_LEVELS) exit_ = true;
		else
		{
			levelPassed_ = false;
			level_++;
			loadNextLevel();
		}
	}
	*/

	GameState::update();
}

void PlayState::render() const
{
	GameState::render();
}

void PlayState::handleEvent(SDL_Event& e)
{
	/*
	if (e.type ...  SDL_p)
		app->getStateMachine()->pushState(new PauseState(game));
	else GameState::handleEvent(e);
	*/
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			SDLApp::toPause(app_);
		else if (e.key.keysym.sym == SDLK_n)
			SDLApp::toEnd(app_);
	}

	GameState::handleEvent(e);
}
