#include "ArrowsGameObject.h"

#include "GameState.h"

void ArrowsGameObject::render() const
{
	texture_->renderFrame(getDestRect(), 0, 0, angle_);
}

void ArrowsGameObject::update()
{
	Vector2D vel = dir_ * speed_;
	pos_ = pos_ + vel;
}

void ArrowsGameObject::loadFromFile(std::ifstream& file)
{
	file >> pos_ >> dir_ >> speed_ >> width_ >> height_ >> angle_;

	// Si vas a guardar una posicion fuera de la pantalla lanza un error
	if (pos_.getX() < 0 || pos_.getX() > WIN_WIDTH || pos_.getY() < -height_ || pos_.getY() > WIN_HEIGHT)
		throw FileFormatError("Position out of bounds. \n");
}

void ArrowsGameObject::saveToFile(std::ofstream& file)
{
	file << pos_ << " " << dir_ << " " << speed_ << " " << width_ << " " << height_ << " " << angle_ << " ";
}