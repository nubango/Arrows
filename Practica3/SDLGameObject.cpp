#include "SDLGameObject.h"

void SDLGameObject::render() const
{
	texture_->renderFrame(getDestRect(), 0, 0, 0);
}

void SDLGameObject::update()
{
	;
}