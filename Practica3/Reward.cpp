#include "Reward.h"

#include "GameState.h"
#include "PlayState.h"

int Reward::count = 0;

void Reward::animate()
{
	int cols = texture_->getNumCols();
	int timeperframe = REWARD_ANIMATION_TIME / cols;

	frame_ = int((SDL_GetTicks() / timeperframe) % cols);
}

Reward::Reward() :
	ArrowsGameObject(), EventHandler(), type_(0), frame_(0), punctured_(false), bubbleTex_(nullptr), used_(false)
{
}

Reward::Reward(Vector2D pos, Vector2D dir, int width, int height, double speed, int angle, Texture* texture, GameState* state, Texture* bubbleTex) :
	ArrowsGameObject(pos, width, height, texture, state, dir, speed, angle), EventHandler(), frame_(0), punctured_(false), bubbleTex_(bubbleTex), used_(false)
{
	type_ = rand() % REWARD_TYPES;
	count++;
}

Reward::~Reward()
{
}

void Reward::render() const
{
	texture_->renderFrame(getDestRect(), type_, frame_, angle_);
	if (!punctured_)
		bubbleTex_->render(getCollisionRect());
}

void Reward::update()
{
	ArrowsGameObject::update();
	if (!punctured_)
	{
		if (static_cast<PlayState*>(state_)->hitBubble(this))
			punctured_ = true;
	}
	else
		animate();

	if (pos_.getY() > WIN_HEIGHT || used_)
		static_cast<PlayState*>(state_)->killReward(lastIt_, itHandler_);
}

bool Reward::handleEvent(SDL_Event& event)
{
	if (!punctured_)
		return false;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_Point p;
		SDL_GetMouseState(&p.x, &p.y);

		if (event.button.button == SDL_BUTTON_LEFT && SDL_PointInRect(&p, &getDestRect()))
		{
			if (type_ == 0) static_cast<PlayState*>(state_)->nextLevel();
			else if (type_ == 1) static_cast<PlayState*>(state_)->addArrows(2);

			used_ = true;
			return true;
		}
	}
	return false;
}

SDL_Rect Reward::getCollisionRect() const
{
	return { (int)pos_.getX() - height_ / 3, (int)pos_.getY() - 3 * width_ / 5, width_ + width_ / 2, 3 * height_ };
}

void Reward::loadFromFile(std::ifstream& file)
{
	ArrowsGameObject::loadFromFile(file);
	file >> type_ >> frame_ >> punctured_;
}

void Reward::saveToFile(std::ofstream& file)
{
	ArrowsGameObject::saveToFile(file);
	file << type_ << " " << frame_ << " " << punctured_ << " ";
}
