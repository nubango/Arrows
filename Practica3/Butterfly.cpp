#include "Butterfly.h"

#include "GameState.h"

int Butterfly::count = 0;

void Butterfly::animate()
{
	int cols = texture_->getNumCols();
	int timeperframe = BUTTERFLY_ANIMATION_TIME / cols;

	frame_ = int((SDL_GetTicks() / timeperframe) % cols);

	// Si mira hacia la derecha
	if (dir_.getX() == 1)
		row_ = 1;
	// Si mira hacia la izquierda
	else
		row_ = 0;
}

void Butterfly::deadAnimation()
{
	frame_ = 0;
	dir_.setY(1);
	dir_.setX(0);
}

void Butterfly::randomMovement()
{
	Uint32 elapsedTime = SDL_GetTicks() - lastTime_;
	if (elapsedTime > TIME_TO_CHANGE_DIR)
	{
		int sx = rand() % 2;
		int sy = rand() % 2;
		sx == 0 ? dir_.setX(1) : dir_.setX(-1);
		sy == 0 ? dir_.setY(1) : dir_.setY(-1);
		lastTime_ = SDL_GetTicks();
	}

	if (pos_.getX() + dir_.getX() * speed_ < MARGIN_BUTTERFLY)
	{
		lastTime_ = SDL_GetTicks();
		dir_.setX(1);
	}
	else if (pos_.getX() + dir_.getX() * speed_ > WIN_WIDTH)
	{
		lastTime_ = SDL_GetTicks();
		dir_.setX(-1);
	}
	else if (pos_.getY() + dir_.getY() * speed_ < 0)
	{
		lastTime_ = SDL_GetTicks();
		dir_.setY(1);
	}
	else if (pos_.getY() + dir_.getY() * speed_ > WIN_HEIGHT)
	{
		lastTime_ = SDL_GetTicks();
		dir_.setY(-1);
	}
}

Butterfly::Butterfly() :
	ArrowsGameObject(), row_(0), frame_(0), lastTime_(0), dead_(false)
{
}

Butterfly::Butterfly(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state) :
	ArrowsGameObject(pos, width, height, texture, state, dir, speed, angle), row_(0), frame_(0), dead_(false)

{
	lastTime_ = SDL_GetTicks();

	int sx = rand() % 2;
	int sy = rand() % 2;
	sx == 0 ? dir_.setX(1) : dir_.setX(-1);
	sy == 0 ? dir_.setY(1) : dir_.setY(-1);

	int x = rand() % SPAWN_SPACE + SPAWN_LOWER_BOUND;
	int y = rand() % WIN_HEIGHT + 100;
	pos_.setX(x);
	pos_.setY(y);

	count++;
}

Butterfly::~Butterfly()
{
}

void Butterfly::render() const
{
	texture_->renderFrame(getDestRect(), row_, frame_, angle_);
}

void Butterfly::update()
{
	if (!dead_)
	{
		//dead_ = game_->hitButterfly(this);
		if (dead_)
		{
			deadAnimation();
			count--;
		}
		randomMovement();
		animate();
	}
	else if (pos_.getY() > WIN_HEIGHT)
		//game_->killButterfly(lastIt_);
		;

	ArrowsGameObject::update();
}

void Butterfly::loadFromFile(std::ifstream& file)
{
	ArrowsGameObject::loadFromFile(file);
	file >> row_ >> frame_;
}

void Butterfly::saveToFile(std::ofstream& file)
{
	ArrowsGameObject::saveToFile(file);
	file << row_ << " " << frame_ << " ";
}
