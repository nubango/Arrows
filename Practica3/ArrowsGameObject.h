#ifndef _ARROWSGAMEOBJECT_H_
#define _ARROWSGAMEOBJECT_H_

#include "checkML.h"
#include "SDLGameObject.h"
#include "FileFormatError.h"

#include <fstream>
#include <list>

class GameState;

class ArrowsGameObject :
	public SDLGameObject
{
protected:
	Vector2D dir_;
	double speed_;

	int angle_;

	std::list<GameObject*>::iterator lastIt_;

	ArrowsGameObject() : SDLGameObject(), dir_({ 0,0 }), speed_(0), angle_(0) {}

	ArrowsGameObject(Vector2D pos, int width, int height, Texture* texture, GameState* state, Vector2D dir, double speed, double angle) :
		SDLGameObject(pos, width, height, texture, state), dir_(dir), speed_(speed), angle_(angle) {}

public:
	virtual ~ArrowsGameObject() {}

	void setItList(const std::list<GameObject*>::iterator& it) { lastIt_ = it; }

	SDL_Rect getCollisionRect() const { return { (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ }; }

	virtual void render() const;
	virtual void update();
	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);

};

#endif // !_ARROWSGAMEOBJECT_H_