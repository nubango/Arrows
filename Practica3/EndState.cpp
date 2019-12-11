#include "EndState.h"

#include "SDLApp.h" 

EndState::EndState(SDLApp* app, bool end) :
	GameState(app), win_(end)
{
	MenuButton* button = new MenuButton({ 400, 550 }, BUTTON_WIDTH, BUTTON_HEIGHT, app_->getTexture("MENU"), this, SDLApp::toMenu);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ 680, 550 }, BUTTON_WIDTH, BUTTON_HEIGHT, app_->getTexture("EXIT"), this, SDLApp::quitApp);
	addEventHandler(button);
	addGameObject(button);
}

EndState::~EndState()
{
}

void EndState::render() const
{
	app_->getTexture("BACKGROUND_SPRING")->render({ 0,0,WIN_WIDTH,WIN_HEIGHT });

	if (win_)
		app_->getTexture("WIN")->render({ (WIN_WIDTH / 2) - 225, (WIN_HEIGHT / 2), 450, 200 });
	else
		app_->getTexture("LOSE")->render({ (WIN_WIDTH / 2) - 225, (WIN_HEIGHT / 2), 450, 200 });

	GameState::render();
}

void EndState::update()
{
	GameState::update();
}

void EndState::handleEvent(SDL_Event& e)
{
	GameState::handleEvent(e);
}
