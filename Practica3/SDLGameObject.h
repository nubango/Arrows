#ifndef _SDLGAMEOBJECT_H_
#define _SDLGAMEOBJECT_H_

#include "checkML.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

class GameState;

class SDLGameObject :
	public GameObject
{
protected:
	Vector2D pos_;
	int width_;
	int height_;

	Texture* texture_;
	GameState* state_;

	SDLGameObject() :
		GameObject(), pos_(0, 0), width_(0), height_(0), texture_(nullptr), state_(nullptr) {}

	SDLGameObject(Vector2D pos, int width, int height, Texture* texture, GameState* state) :
		GameObject(), pos_(pos), width_(width), height_(height), texture_(texture), state_(state) {}

public:
	~SDLGameObject() {}

	SDL_Rect getDestRect() const { return { (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ }; }

	virtual void render() const = 0;
	virtual void update() = 0;
};

#endif // !_SDLGAMEOBJECT_H_