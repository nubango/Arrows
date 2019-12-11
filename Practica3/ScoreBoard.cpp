#include "ScoreBoard.h"

#include "SDLApp.h"

ScoreBoard::ScoreBoard() :
	GameObject(), app_(nullptr), score_(0), numArrows_(0)
{
}

ScoreBoard::ScoreBoard(SDLApp* app) :
	GameObject(), app_(app), score_(0), numArrows_(MAX_ARROWS)
{
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::render() const
{
	// HUD: flechas
	for (int i = 0; i < numArrows_; i++)
		app_->getTexture("ARROW_UI")->render({ (WIN_WIDTH / 4) + (15 * i), 10, 15, 60 });

	// HUD: puntuacion
	unsigned int centenas = score_ / 100;
	unsigned int decenas = (score_ % 100) / 10;
	unsigned int unidades = (score_ % 10);

	app_->getTexture("DIGITS")->renderFrame({ (WIN_WIDTH / 4) - 100, 15, 30, 45 }, 0, centenas);
	app_->getTexture("DIGITS")->renderFrame({ (WIN_WIDTH / 4) - 70, 15, 30, 45 }, 0, decenas);
	app_->getTexture("DIGITS")->renderFrame({ (WIN_WIDTH / 4) - 40, 15, 30, 45 }, 0, unidades);
}

void ScoreBoard::update()
{
}