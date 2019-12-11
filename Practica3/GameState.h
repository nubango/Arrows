#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "checkML.h"
#include "consts.h"
#include "SDLGameObject.h"
#include "EventHandler.h"

#include <list>

// Enum para getStateName
enum StateName { MENU_STATE, PLAY_STATE, PAUSE_STATE, END_STATE };

class SDLApp;

// Es la clase raiz de estados del juego
class GameState
{
protected:
	std::list<GameObject*> stage_; // Escenario del estado del juego
	std::list<EventHandler*> eventHandlers_; // Manejadores de eventos
	SDLApp* app_; // Puntero al juego

	GameState() : app_(nullptr) {}
	// Clase abstracta porque no tiene constructora publica
	GameState(SDLApp* app) : app_(app) {}

	// Agrega a la lista de iteradores el objeto a
	void addGameObject(SDLGameObject* a);
	// Agrega a la lista de iteradores el handler e
	void addEventHandler(EventHandler* e);

public:
	virtual ~GameState();

	virtual void update();
	virtual void render() const;
	virtual void handleEvent(SDL_Event& e);

	virtual StateName getStateName() = 0;
	SDLApp* getApp() { return app_; }
};

#endif // !_GAMESTATE_H_