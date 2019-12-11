#include "MenuButton.h"

MenuButton::MenuButton() : currentState_(MouseOut), cbOnClick_(nullptr)
{
}

MenuButton::MenuButton(Vector2D pos, int width, int height, Texture* texture, GameState* state, CallBackOnClick* cb) : EventHandler(), SDLGameObject(pos, width, height, texture, state), currentState_(MouseOver), cbOnClick_(cb)
{
}

MenuButton::~MenuButton()
{
}

void MenuButton::render() const
{
	texture_->renderFrame(getDestRect(), 0, currentState_);
}

void MenuButton::update()
{
}

bool MenuButton::handleEvent(SDL_Event& e)
{
	// Cuando el raton pulsa el boton
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point p = { e.button.x, e.button.y };
		if (SDL_PointInRect(&p, &getDestRect()))
		{
			currentState_ = MouseClick;
			return true;
		}
	}
	// Cuando el raton despulsa el boton
	if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point p = { e.button.x, e.button.y };
		if (SDL_PointInRect(&p, &getDestRect()))
		{
			currentState_ = MouseOver;
			cbOnClick_(state_->getApp());
			return true;
		}
	}
	// Cuando el raton pasa por encima del boton o no
	if (e.type == SDL_MOUSEMOTION)
	{
		SDL_Point p = { e.motion.x, e.motion.y };
		if (SDL_PointInRect(&p, &getDestRect()))
		{
			currentState_ = MouseOver;
			return true;
		}
		else
			currentState_ = MouseOut;
	}
	return false;
}