#ifndef _BOW_H_
#define _BOW_H_

#include "checkML.h"
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "Arrow.h"

class GameState;

class Bow :
	public ArrowsGameObject, public EventHandler
{
private:

	bool loaded_; // Estado del arco (cargado/no cargado)
	Arrow* arrow_;
	Texture* otherTexture_; // Textura para cargado/descargado
	unsigned int drawTime_;

public:
	Bow();
	Bow(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state, Texture* other);

	virtual ~Bow();

	virtual void render() const;
	virtual void update();
	virtual bool handleEvent(SDL_Event& event);
};

#endif // !_BOW_H_