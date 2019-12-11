#ifndef _REWARD_H_
#define _REWARD_H_

#include "checkML.h"
#include "ArrowsGameObject.h"
#include "EventHandler.h"

class GameState;

class Reward :
	public ArrowsGameObject, public EventHandler
{
public:
	static int count;

private:
	int type_; // fila de la spritesheet
	int frame_; // frame de la animacion

	bool punctured_; // Estado (pinchado/no pinchado)
	bool used_; // Estado (usado/no usado)

	Texture* bubbleTex_;

	void animate();

public:
	Reward();
	Reward(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state, Texture* bubbleTex);
	virtual ~Reward();

	virtual void render() const;
	virtual void update();
	virtual bool handleEvent(SDL_Event& event);

	virtual SDL_Rect getCollisionRect() const;

	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);
};

#endif // !_REWARD_H_