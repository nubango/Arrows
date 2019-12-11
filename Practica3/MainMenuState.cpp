#include "MainMenuState.h"

#include "SDLApp.h"

MainMenuState::MainMenuState(SDLApp* app) :
	GameState(app)
{
	MenuButton* button = new MenuButton({ 180, 500 }, 200, 80, app_->getTexture("LOAD"), this, SDLApp::loadPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ 465, 450 }, 350, 200, app_->getTexture("PLAY"), this, SDLApp::toPlay);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ 900, 500 }, 200, 80, app_->getTexture("EXIT"), this, SDLApp::quitApp);
	addEventHandler(button);
	addGameObject(button);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::render() const
{
	app_->getTexture("BACKGROUND_AUTUMN")->render({ 0,0,WIN_WIDTH,WIN_HEIGHT });
	app_->getTexture("LOGO")->render({ 300, 50, 640, 360 });
	GameState::render();
}

void MainMenuState::update()
{
	GameState::update();
}

void MainMenuState::handleEvent(SDL_Event& e)
{
	GameState::handleEvent(e);
}