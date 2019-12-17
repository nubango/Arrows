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
		app_->getTexture("ARROW_UI")->render({ (WIN_WIDTH / 4) + (UI_ARROWS_WIDTH * i), UI_SCORE_POS_Y, UI_ARROWS_WIDTH, UI_ARROWS_HEIGHT });

	// HUD: puntuacion
	Texture* t = new Texture(app_->getRenderer());
	


	t->loadFont(std::to_string(score_), app_->getFont("PAINT72"), { 255, 255, 255, 255 });
	int w, h;
	app_->getFont("PAINT72")->getSizeOfText(std::to_string(score_), w, h);
	t->render({ UI_SCORE_POS_X, UI_SCORE_POS_Y, w, h });

	delete t;
	t = nullptr;
}

void ScoreBoard::update()
{
}