#ifndef _SDLGAMEOBJECT_H_
#define _SDLGAMEOBJECT_H_

#include "checkML.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "SDLApp.h"

class SDLGameObject :
	public GameObject
{
private:
	Vector2D pos_;
	int width_;
	int height_;

	Texture* texture_;
	SDLApp* app_;

public:
	SDLGameObject() : 
		GameObject(), pos_(0, 0), width_(0), height_(0), texture_(nullptr), app_(nullptr) {}
	SDLGameObject(Vector2D pos, int width, int height, Texture* texture, SDLApp* app) : 
		GameObject(), pos_(pos), width_(width), height_(height), texture_(texture), app_(app) {}
	~SDLGameObject() {}

	SDL_Rect getDestRect() const { return { (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ }; }

	virtual void render() const;
	virtual void update();
};

#endif // !_SDLGAMEOBJECT_H_