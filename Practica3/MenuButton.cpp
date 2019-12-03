#include "MenuButton.h"

bool MenuButton::handleEvent(SDL_Event& e)
{
	bool handled = false;
	if (e.type == SDL_MOUSEBUTTONUP /*&& e.button.button == ...*/)
	{
		SDL_Point p = { e.button.x, e.button.y };
		SDL_Rect r = { x_,y_,w_,h_ };
		if (SDL_PointInRect(&p, &r) == SDL_TRUE)
		{
			//cbOnClick_(->game);
			handled = true;
		}
	}
	return handled;
}