#include "PauseState.h"

#include "SDLApp.h"

PauseState::PauseState(SDLApp* app) :
	GameState(app)
{
	MenuButton* button = new MenuButton({ 180, 500 }, BUTTON_WIDTH, BUTTON_HEIGHT, app_->getTexture("SAVE"), this, SDLApp::savePlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ 465, 450 }, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT, app_->getTexture("RESUME"), this, SDLApp::resumeApp);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ 900, 500 }, BUTTON_WIDTH, BUTTON_HEIGHT, app_->getTexture("MENU"), this, SDLApp::toMenu);
	addEventHandler(button);
	addGameObject(button);
}

PauseState::~PauseState()
{
}

void PauseState::render() const
{
	app_->getTexture("BACKGROUND_SPRING")->render({ 0,0,WIN_WIDTH,WIN_HEIGHT });
	GameState::render();
}

void PauseState::update()
{
	GameState::update();
}

void PauseState::handleEvent(SDL_Event& e)
{
	GameState::handleEvent(e);
}