#ifndef _ARROW_H_
#define _ARROW_H_

#include "checkML.h"
#include "ArrowsGameObject.h"

class GameState;

class Arrow :
	public ArrowsGameObject
{
public:
	static int count;

private:
	int numHits_;

public:
	Arrow();
	Arrow(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state);
	virtual ~Arrow();

	virtual void update();
	virtual SDL_Rect getCollisionRect() const;

	int getNumHits() { return numHits_; }
	void addHit() { numHits_++; }
};

#endif // !_ARROW_H_