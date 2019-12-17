#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "checkML.h"
#include "GameState.h"
#include "Arrow.h"
#include "Bow.h"
#include "Balloon.h"
#include "Butterfly.h"
#include "Reward.h"
#include "ScoreBoard.h"

#include <time.h>

class SDLApp;

class PlayState :
	public GameState
{
private:
	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;
	std::list<Butterfly*> butterflies_;
	std::list<Reward*> rewards_;
	std::list<std::list<GameObject*>::iterator> objectsToErase_;

	Bow* bow_;
	ScoreBoard* scoreBoard_;

	int lastSpawnTime_;
	int currentLevel_;
	bool changeLevel_;
	bool win_;

	// Borra las listas
	void clear();
	// Borra los iteradores de objects to erase
	void eraseObjects();
	// Crea el scoreBoard y el bow
	void init();
	// Suma uno al nivel y crea las mariposas
	void changeLevel();

	void generateButterflies();
	void generateBalloons();

	void addArrow(Arrow* a);
	void addBalloon(Balloon* b);
	void addButterfly(Butterfly* b);
	void addRewardBubble(Reward* r);

public:
	PlayState() : GameState(), bow_(nullptr), scoreBoard_(nullptr), lastSpawnTime_(0), currentLevel_(0), changeLevel_(false), win_(false) {}
	PlayState(SDLApp* app);
	virtual ~PlayState();

	virtual void update();
	virtual void render() const;
	virtual void handleEvent(SDL_Event& e);

	virtual StateName getStateName() { return StateName::PLAY_STATE; }

	// Lanza una flecha nueva
	void createArrow(Arrow* arrow);

	// Comprueba si alguna punta de flecha pincha un globo dado
	bool hitBalloon(Balloon* balloon);
	// Comprueba si alguna punta de flecha pincha una mariposa dada
	bool hitButterfly(Butterfly* butterfly);
	// Comprueba si alguna punta de flecha pincha una burbuja de reward dada
	bool hitBubble(Reward* reward);

	// Elimina de las listas de cada objeto
	void killArrow(std::list<GameObject*>::iterator it);
	void killBalloon(std::list<GameObject*>::iterator it);
	void killButterfly(std::list<GameObject*>::iterator it);
	void killReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator eit);

	// Incluye el iterador en la lista de objectsToErase
	void killGameObject(std::list<GameObject*>::iterator it);

	// METODOS DE REWARDS
	// Pasa el nivel cuando se consigue el reward especifico
	void nextLevel() { changeLevel_ = true; }
	// Suma n flechas a las flechas disponibles
	void addArrows(int n) { scoreBoard_->setNumArrows(scoreBoard_->getNumArrows() + n); }

	// Guarda en archivo la informacion de la partida
	void saveToFile(int code);
	// Lee de archivo para cargar la partida
	void loadFromFile(int code);

	int getAvailableArrows() { return scoreBoard_->getNumArrows(); }
	int getScore() { return scoreBoard_->getScore(); }
	bool hasWon() { return win_; }
};

#endif // !_PLAYSTATE_H_