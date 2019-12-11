#include "Bow.h"

#include "GameState.h"
#include "SDLApp.h"

Bow::Bow() :
	ArrowsGameObject(), EventHandler(), loaded_(false), arrow_(nullptr), drawTime_(0), otherTexture_(nullptr)
{
}

Bow::Bow(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state, Texture* other) :
	ArrowsGameObject(pos, width, height, texture, state, dir, speed, angle), EventHandler(), loaded_(false), arrow_(nullptr), drawTime_(0), otherTexture_(other)
{
}

Bow::~Bow()
{
}

void Bow::render() const
{
	// No se usa ArrowsGameObject::render() porque se usan dos texturas
	// y la principal necesita reescalado

	if (loaded_)
	{
		otherTexture_->renderFrame(getDestRect(), 0, 0, angle_);
	}
	else
	{
		SDL_Rect destRect = { (int)pos_.getX() + 30, (int)pos_.getY(), (width_ / 5) * 2, height_ };
		texture_->renderFrame(destRect, 0, 0, angle_);
	}
}

void Bow::update()
{
	Point2D nextPos;
	nextPos = pos_ + dir_ * speed_;
	// Solo se mueve si la siguiente posicion es valida
	if (nextPos.getY() > 0 && nextPos.getY() < (WIN_HEIGHT - height_))
		pos_ = nextPos;
}

bool Bow::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) dir_.setY(1);
		else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) dir_.setY(-1);
		else if (event.key.keysym.sym == SDLK_e)
		{
			if (angle_ < ANGLE_LIMIT)
				angle_ += speed_;
		}
		else if (event.key.keysym.sym == SDLK_q)
		{
			if (angle_ > -ANGLE_LIMIT)
				angle_ -= speed_;
		}
		else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
		{
			if (static_cast<PlayState*>(state_)->getAvailableArrows() > 0)
			{
				drawTime_ = SDL_GetTicks();
				loaded_ = true;
			}
		}
		else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
		{
			if (loaded_)
			{
				double drawFactor = 1.0 + ((SDL_GetTicks() - drawTime_) / 1000.0);
				Vector2D pos = { pos_.getX(), pos_.getY() + 60 };
				arrow_ = new Arrow(pos, { 1,0 },
					ARROW_WIDTH, ARROW_HEIGHT, ARROW_SPEED * drawFactor, angle_, state_->getApp()->getTexture("ARROW"), state_);

				static_cast<PlayState*>(state_)->createArrow(arrow_);
				loaded_ = false;
			}
		}
		return true;
	}
	if (event.type == SDL_KEYUP)
	{
		dir_.setY(0);
		return true;
	}

	return false;
}
