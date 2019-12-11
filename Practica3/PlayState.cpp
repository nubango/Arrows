#include "PlayState.h"

#include "SDLApp.h"

PlayState::PlayState(SDLApp* app) :
	GameState(app), bow_(nullptr), lastSpawnTime_(0), currentLevel_(0), changeLevel_(false), win_(false)
{
	srand(static_cast<unsigned int>(time(NULL)));

	init();
	changeLevel();
}

PlayState::~PlayState()
{
	clear();
}

void PlayState::update()
{
	generateBalloons();

	GameState::update();

	eraseObjects();

	// Con la suficiente puntuacion pasas de nivel
	if (scoreBoard_->getScore() > POINTS_PER_LEVEL* currentLevel_ || changeLevel_)
		changeLevel();

	// Si no quedan flechas y ya han salido todas de la pantalla(las lanzadas) 
	// Si no quedan mariposas 
	if (scoreBoard_->getNumArrows() == 0 && arrows_.empty() || Butterfly::count == 0)
		SDLApp::toEnd(app_);
}

void PlayState::render() const
{
	app_->getTexture("BACKGROUND_" + currentLevel_)->render({ 0,0,WIN_WIDTH,WIN_HEIGHT });

	GameState::render();

	scoreBoard_->render();
}

void PlayState::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			SDLApp::toPause(app_);
		else if (e.key.keysym.sym == SDLK_n)
			SDLApp::toEnd(app_);
	}

	GameState::handleEvent(e);
}

void PlayState::createArrow(Arrow* arrow)
{
	addArrow(arrow);
	scoreBoard_->useArrow();
}

bool PlayState::hitBalloon(Balloon* balloon)
{
	bool collision = false;
	SDL_Rect B = balloon->getCollisionRect();

	auto it = arrows_.begin();
	while (it != arrows_.end() && !collision)
	{
		SDL_Rect A = (*it)->getCollisionRect();
		collision = SDL_HasIntersection(&A, &B);

		// Para no perder la flecha que colisiona
		if (!collision)
			it++;
	}
	if (collision)
	{
		// Accedemos a la flecha 
		(*it)->addHit();
		int score = scoreBoard_->getScore();
		score += ((*it)->getNumHits() - 1) * ((*it)->getNumHits() - 1) * POINTS_PER_BALLOON;
		if (score > 999) score = 999;
		scoreBoard_->setScore(score);

		// Hay un 30 % de probabilidades de que salga un reward
		if (rand() % 100 < 30)
		{
			Reward* r = new Reward({ (double)B.x,(double)B.y + B.h }, { 0,1 }, REWARD_WIDTH, REWARD_HEIGHT, REWARD_SPEED, 0, app_->getTexture("REWARD"), this, app_->getTexture("BUBBLE"));
			addRewardBubble(r);
		}
	}
	return collision;
}

bool PlayState::hitButterfly(Butterfly* butterfly)
{
	bool collision = false;
	SDL_Rect B = butterfly->getCollisionRect();

	auto it = arrows_.begin();
	while (it != arrows_.end() && !collision)
	{
		SDL_Rect A = (*it)->getCollisionRect();
		collision = SDL_HasIntersection(&A, &B);
		// Para no perder la flecha que colisiona
		if (!collision)
			it++;
	}
	if (collision)
	{
		int score = scoreBoard_->getScore();
		score -= POINTS_PER_BALLOON / 2;
		if (score < 0) score = 0;
		scoreBoard_->setScore(score);
	}
	return collision;
}

bool PlayState::hitBubble(Reward* reward)
{
	bool collision = false;
	SDL_Rect B = reward->getCollisionRect();

	auto it = arrows_.begin();
	while (it != arrows_.end() && !collision)
	{
		SDL_Rect A = (*it)->getCollisionRect();
		collision = SDL_HasIntersection(&A, &B);
		it++;
	}
	return collision;
}

void PlayState::killArrow(std::list<GameObject*>::iterator it)
{
	arrows_.remove(static_cast<Arrow*>((*it)));
	killGameObject(it);
	Arrow::count--;
}

void PlayState::killBalloon(std::list<GameObject*>::iterator it)
{
	balloons_.remove(static_cast<Balloon*>((*it)));
	killGameObject(it);
}

void PlayState::killButterfly(std::list<GameObject*>::iterator it)
{
	butterflies_.remove(static_cast<Butterfly*>((*it)));
	killGameObject(it);
}

void PlayState::killReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator eit)
{
	rewards_.remove(static_cast<Reward*>((*it)));
	eventHandlers_.remove((*eit));
	killGameObject(it);
	Reward::count--;
}

void PlayState::killGameObject(std::list<GameObject*>::iterator it)
{
	objectsToErase_.push_back(it);
}

void PlayState::saveToFile(int code)
{
	std::ofstream file;
	file.open(std::to_string(code) + ".txt");

	if (!file.is_open())
		throw FileNotFoundError("Couldn´t open " + std::to_string(code) + ".txt\n");

	// Se guarda el nivel, la puntacion y las flechas disponibles
	file << currentLevel_ << " " << scoreBoard_->getScore() << " " << scoreBoard_->getNumArrows() << std::endl;

	// Se guarda el arco
	bow_->saveToFile(file);
	file << std::endl;

	// Se guardan las flechas
	file << Arrow::count << std::endl;
	for (Arrow* a : arrows_)
	{
		a->saveToFile(file);
		file << std::endl;
	}

	// Se guardan los globos
	file << Balloon::count << std::endl;
	for (Balloon* b : balloons_)
	{
		if (!b->isPunctured())
		{
			b->saveToFile(file);
			file << std::endl;
		}
	}

	// Se guardan las mariposas
	file << Butterfly::count << std::endl;
	for (Butterfly* b : butterflies_)
	{
		if (!b->isDead())
		{
			b->saveToFile(file);
			file << std::endl;
		}
	}
	// Se guardan los premios
	file << Reward::count << std::endl;
	for (Reward* r : rewards_)
	{
		r->saveToFile(file);
		file << std::endl;
	}

	file.close();
}

void PlayState::loadFromFile(int code)
{
	clear();
	init();

	std::ifstream file;
	file.open(std::to_string(code) + ".txt");

	if (!file.is_open())
		throw FileNotFoundError("Couldn't open " + std::to_string(code) + ".txt\n");

	int s, a;
	// Se carga el nivel, la puntuacion y las flechas disponibles
	file >> currentLevel_ >> s >> a;

	if (currentLevel_ < 0 || s < 0 || a < 0)
		throw FileFormatError("Negative values detected. \n");

	scoreBoard_->setScore(s);
	scoreBoard_->setNumArrows(a);

	// Se carga el arco
	bow_->loadFromFile(file);

	// Se cargan las flechas
	int count = 0;
	file >> count;
	for (int i = 0; i < count; i++)
	{
		Arrow* a = new Arrow({ 0,0 }, { 0,0 },
			ARROW_WIDTH, ARROW_HEIGHT, 0, 0, app_->getTexture("ARROW"), this);
		a->loadFromFile(file);
		addArrow(a);
	}

	// Se cargan los globos
	file >> count;
	for (int i = 0; i < count; i++)
	{
		Balloon* b = new Balloon({ 0, 0 }, { 0,0 }, BALLOON_WIDTH, BALLOON_HEIGHT, 0, 0, app_->getTexture("BALLOON"), this);
		b->loadFromFile(file);
		addBalloon(b);
	}

	// Se cargan las mariposas
	file >> count;
	for (int i = 0; i < count; i++)
	{
		Butterfly* b = new Butterfly({ 0, 0 }, { 0,0 }, BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT, 0, 0, app_->getTexture("BUTTERFLY"), this);
		b->loadFromFile(file);
		addButterfly(b);
	}

	// Se cargan los premios
	file >> count;
	for (int i = 0; i < count; i++)
	{
		Reward* r = new Reward({ 0, 0 }, { 0,0 }, REWARD_WIDTH, REWARD_HEIGHT, 0, 0, app_->getTexture("REWARD"), this, app_->getTexture("BUBBLE"));
		r->loadFromFile(file);
		addRewardBubble(r);
	}

	file.close();
}

void PlayState::init()
{
	Arrow::count = 0;
	Balloon::count = 0;
	Butterfly::count = 0;
	Reward::count = 0;

	scoreBoard_ = new ScoreBoard(app_);
	scoreBoard_->setNumArrows(MAX_ARROWS);

	bow_ = new Bow({ 0,100 }, { 0,0 }, BOW_WIDTH, BOW_HEIGHT, BOW_SPEED, 0, app_->getTexture("BOW"), this, app_->getTexture("LOADED_BOW"));
	addGameObject(bow_);
	addEventHandler(bow_);
}

void PlayState::clear()
{
	delete scoreBoard_;
	scoreBoard_ = nullptr;

	for (GameObject* o : stage_)
	{
		delete o;
		o = nullptr;
	}

	stage_.clear();
	arrows_.clear();
	balloons_.clear();
	eventHandlers_.clear();
	butterflies_.clear();
	rewards_.clear();
	objectsToErase_.clear();
}

void PlayState::eraseObjects()
{
	auto it = objectsToErase_.begin();
	while (it != objectsToErase_.end())
	{
		delete (**it);
		**it = nullptr;
		stage_.erase(*it);
		it++;
	}
	objectsToErase_.clear();
}

void PlayState::changeLevel()
{
	if (currentLevel_ < NUM_LEVELS)
	{
		currentLevel_++;
		int score = scoreBoard_->getScore();

		// Reseteamos los objetos
		clear();

		// Creamos los objetos basicos
		init();

		generateButterflies();

		scoreBoard_->setScore(score);
	}
	else
		win_ = true;

	changeLevel_ = false;
}

void PlayState::generateButterflies()
{
	for (int i = 0; i < BUTTERFLIES_PER_LEVEL * currentLevel_; i++)
	{
		Butterfly* b = new Butterfly({ 0,0 }, { 0,0 }, BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT, BUTTERFLY_SPEED, 0, app_->getTexture("BUTTERFLY"), this);
		addButterfly(b);
	}
}

void PlayState::generateBalloons()
{
	int elapsedTime = SDL_GetTicks() - lastSpawnTime_;
	if (elapsedTime > SPAWN_TIME)
	{
		double rndx = rand() % SPAWN_SPACE + SPAWN_LOWER_BOUND;

		Balloon* b = new Balloon({ rndx,WIN_HEIGHT }, { 0,-1 }, BALLOON_WIDTH, BALLOON_HEIGHT, 0, 0, app_->getTexture("BALOON"), this);

		addBalloon(b);

		lastSpawnTime_ = SDL_GetTicks();
	}
}

void PlayState::addArrow(Arrow* a)
{
	arrows_.push_back(a);
	addGameObject(a);
}

void PlayState::addBalloon(Balloon* b)
{
	balloons_.push_back(b);
	addGameObject(b);
}

void PlayState::addButterfly(Butterfly* b)
{
	butterflies_.push_back(b);
	addGameObject(b);
}

void PlayState::addRewardBubble(Reward* r)
{
	rewards_.push_back(r);
	addGameObject(r);
	addEventHandler(r);
}