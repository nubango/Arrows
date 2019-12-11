#include "GameStateMachine.h"

GameStateMachine::GameStateMachine()
{
}

GameStateMachine::~GameStateMachine()
{
	// Vacia la pila
	while (!states_.empty())
		popState();
}

GameState* GameStateMachine::currentState() const
{
	if (!states_.empty()) return states_.top();
	else return nullptr;
}

void GameStateMachine::pushState(GameState* s)
{
	states_.push(s);
}

void GameStateMachine::changeState(GameState* s)
{
	popState();
	pushState(s);
}

void GameStateMachine::popState()
{
	if (!states_.empty())
	{
		delete states_.top();
		states_.top() = nullptr;
		states_.pop();
	}
}