#ifndef _GAMESTATEMACHINE_H_
#define _GAMESTATEMACHINE_H_

#include "checkML.h"

#include <stack>

class GameState; // Inclusion Circular

class GameStateMachine
{
private:
	std::stack<GameState*> states_; // Pila de estados

public:
	GameStateMachine();
	~GameStateMachine();

	// Devuelve el estado actual
	GameState* currentState() const;
	// Incluye el nuevo estado s en la pila
	void pushState(GameState* s);
	// Cambia el estado actual por el estado s
	void changeState(GameState* s);
	// Elimina el estado en top
	void popState();
};

#endif // !_GAMESTATEMACHINE_H_