#ifndef _BALLOON_H_
#define _BALLOON_H_

#include "checkML.h"
#include "ArrowsGameObject.h"

class GameState;

class Balloon :
	public ArrowsGameObject
{
public:
	static int count;

private:
	int color_; // fila de la spritesheet
	int frame_; // frame de la animacion

	unsigned int punctTime_; // Instante temporal en el que se pincho
	bool punctured_; // Estado del globo (pinchado/no pinchado)

	// Se encarga de la animacion al ser pinchado
	void animate();

public:
	bool isPunctured() { return punctured_; }

	Balloon();
	Balloon(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state);
	virtual ~Balloon();

	virtual void render() const;
	virtual void update();

	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);
};

#endif // !_BALLOON_H_