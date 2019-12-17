#ifndef _ENDSTATE_H_
#define _ENDSTATE_H_

#include "checkML.h"
#include "GameState.h"
#include "MenuButton.h"
#include "LeaderBoard.h"

class SDLApp;

class EndState :
	public GameState
{
private:
	bool win_;

	LeaderBoard* leadBoard_;

	// Renderiza los textos TTF del final de la partida
	void renderMessage() const;

public:
	EndState() : GameState(), win_(false), leadBoard_(nullptr) {}
	EndState(SDLApp* app, bool end, int score);
	virtual ~EndState();

	virtual void render() const;
	virtual void update();
	virtual void handleEvent(SDL_Event& e);

	virtual StateName getStateName() { return StateName::END_STATE; }
};

#endif // !_ENDSTATE_H_