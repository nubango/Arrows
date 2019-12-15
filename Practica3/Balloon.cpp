#include "Balloon.h"

#include "GameState.h"
#include "PlayState.h"

int Balloon::count = 0;

Balloon::Balloon() :
	ArrowsGameObject(), color_(0), frame_(0), punctTime_(0), punctured_(false)
{
}

Balloon::Balloon(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state) :
	ArrowsGameObject(pos, width, height, texture, state, dir, speed, angle), frame_(0), punctTime_(0), punctured_(false)
{
	color_ = rand() % 7;

	speed_ = VEL_BALLOONS_MIN + (rand()) / (RAND_MAX / (double)(VEL_BALLOONS_MAX - VEL_BALLOONS_MIN));

	count++;
}

Balloon::~Balloon()
{
}

void Balloon::render() const
{
	texture_->renderFrame(getDestRect(), color_, frame_, angle_);
}

void Balloon::update()
{
	if (!punctured_)
	{
		ArrowsGameObject::update();
		if (static_cast<PlayState*>(state_)->hitBalloon(this))
		{
			punctTime_ = SDL_GetTicks();
			punctured_ = true;
			count--;
		}
		// Si se sale de la pantalla se elimina
		else if (pos_.getY() < -height_)
		{
			static_cast<PlayState*>(state_)->killBalloon(lastIt_);
			count--;
		}
	}
	else
		animate();
}

void Balloon::loadFromFile(std::ifstream& file)
{
	ArrowsGameObject::loadFromFile(file);
	file >> color_;
}

void Balloon::saveToFile(std::ofstream& file)
{
	ArrowsGameObject::saveToFile(file);
	file << color_ << " ";
}

void Balloon::animate()
{
	int cols = texture_->getNumCols();
	unsigned int timeperframe = BALLOON_ANIMATION_TIME / cols;
	int currentTime = SDL_GetTicks();

	if (frame_ < cols && currentTime - punctTime_ > timeperframe* frame_)
		frame_++;
	else if (frame_ >= cols)
		static_cast<PlayState*>(state_)->killBalloon(lastIt_);
}
