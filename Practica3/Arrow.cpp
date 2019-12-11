#include "Arrow.h"

#include "GameState.h"
#include "PlayState.h"

int Arrow::count = 0;

Arrow::Arrow() :
	ArrowsGameObject(), numHits_(0)
{
}

Arrow::Arrow(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state) :
	ArrowsGameObject(pos, width, height, texture, state, dir, speed, angle), numHits_(1)
{
	dir_.rotate(angle_);
	count++;
}

Arrow::~Arrow()
{
}

void Arrow::update()
{
	ArrowsGameObject::update();
	if (pos_.getX() > WIN_WIDTH || pos_.getY() > WIN_HEIGHT || pos_.getY() < 0)
		static_cast<PlayState*>(state_)->killArrow(lastIt_);
}

SDL_Rect Arrow::getCollisionRect() const
{
	return { (int)pos_.getX() + ((width_ / 4) * 3), (int)pos_.getY(), width_ / 4, height_ };
}