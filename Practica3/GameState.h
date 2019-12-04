#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "checkML.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "SDLApp.h"

#include <list>

// Es la clase raiz de estados del juego
class GameState
{
private:
	std::list<GameObject*> stage_; // Escenario del estado del juego
	std::list<EventHandler*> eventHandlers_; // Manejadores de eventos
	SDLApp* app_; // Puntero al juego

protected:
	// Clase abstracta porque no tiene constructora publica
	GameState(SDLApp* app) : app_(app) {}

public:
	virtual void update();
	virtual void render() const;
	virtual void handleEvent(SDL_Event& e);
};

#endif // !_GAMESTATE_H_