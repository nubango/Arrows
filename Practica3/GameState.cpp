#include "GameState.h"

#include "SDLApp.h"

void GameState::addGameObject(SDLGameObject* a)
{
	std::list<GameObject*>::iterator it = stage_.insert(stage_.end(), a);

	if (dynamic_cast<ArrowsGameObject*>(a))
		static_cast<ArrowsGameObject*>(a)->setItList(it);
}

void GameState::addEventHandler(EventHandler* e)
{
	std::list<EventHandler*>::iterator it = eventHandlers_.insert(eventHandlers_.end(), e);
	e->setItHandler(it);
}

GameState::~GameState()
{
	for (GameObject* o : stage_)
	{
		delete o;
		o = nullptr;
	}

	stage_.clear();
	eventHandlers_.clear();
}

void GameState::update()
{
	for (GameObject* o : stage_)
		o->update();
}

void GameState::render() const
{
	for (GameObject* o : stage_)
		o->render();
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