#include "GameState.h"

void GameState::update()
{
}

void GameState::render() const
{
}

void GameState::handleEvent(SDL_Event& e)
{
	bool handled = false;
	auto it = eventHandlers_.begin();
	while (!handled && it != eventHandlers_.end())
	{
		if ((*it)->handleEvent(e)) handled = true;
		else ++it;
	}
}