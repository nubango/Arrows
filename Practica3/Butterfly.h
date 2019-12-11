#ifndef _BUTTERFLY_H_
#define _BUTTERFLY_H_

#include "checkML.h"
#include "ArrowsGameObject.h"

class GameState;

class Butterfly :
	public ArrowsGameObject
{
public:
	static int count;

private:
	int row_; // fila de la spritesheet
	int frame_; // frame de la animacion
	int lastTime_;

	bool dead_; // estado de la mariposa

	void animate(); // animacion de volar
	void deadAnimation(); // las mariposas caen paralizadas al morir
	void randomMovement(); // movimiento aleatorio por pantalla

public:
	Butterfly();
	Butterfly(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state);
	virtual ~Butterfly();

	bool isDead() { return dead_; }

	virtual void render() const;
	virtual void update();

	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);
};

#endif // !_BUTTERFLY_H_