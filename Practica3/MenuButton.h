#ifndef _MENUBUTTON_H_
#define _MENUBUTTON_H_

#include "checkML.h"
#include "SDLGameObject.h"
#include "EventHandler.h"
#include "SDLApp.h"

using CallBackOnClick = void(SDLApp * app);

class MenuButton :
	public SDLGameObject, public EventHandler
{
private:
	enum ButtonState { MouseOut, MouseOver, MouseClick };

protected:
	CallBackOnClick* cbOnClick_;

	ButtonState currentState_;

public:
	MenuButton();
	MenuButton(Vector2D pos, int width, int height, Texture* texture, GameState* state, CallBackOnClick* cb);
	virtual ~MenuButton();

	virtual void render() const;
	virtual void update();
	virtual bool handleEvent(SDL_Event& e);
};

#endif // !_MENUBUTTON_H_