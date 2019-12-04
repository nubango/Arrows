#ifndef _ARROWSGAMEOBJECT_H_
#define _ARROWSGAMEOBJECT_H_

#include "checkML.h"
#include "SDLGameObject.h"

class ArrowsGameObject :
	public SDLGameObject
{
private:
	Vector2D dir_;
	double speed_;

	int angle_;

	ArrowsGameObject() : SDLGameObject() {}
	ArrowsGameObject(Vector2D pos, int width, int height, Texture* texture, SDLApp* app, Vector2D dir, double speed, double angle) :
		SDLGameObject(pos, width, height, texture, app), dir_(dir), speed_(speed), angle_(angle) {}
};

#endif // !_ARROWSGAMEOBJECT_H_