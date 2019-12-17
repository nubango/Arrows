#include "MainMenuState.h"

#include "SDLApp.h"

MainMenuState::MainMenuState(SDLApp* app) :
	GameState(app)
{
	MenuButton* button = new MenuButton({ 180, 500 }, BUTTON_WIDTH, BUTTON_HEIGHT, app_->getTexture("LOAD"), this, SDLApp::loadPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ 465, 450 }, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT, app_->getTexture("PLAY"), this, SDLApp::toPlay);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ 900, 500 }, BUTTON_WIDTH, BUTTON_HEIGHT, app_->getTexture("EXIT"), this, SDLApp::quitApp);
	addEventHandler(button);
	addGameObject(button);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::render() const
{
	app_->getTexture("BACKGROUND_AUTUMN")->render({ 0,0,WIN_WIDTH,WIN_HEIGHT });
	app_->getTexture("LOGO")->render({ LOGO_POS_X, LOGO_POS_Y, LOGO_WIDTH, LOGO_HEIGHT });

	Texture* t = new Texture(app_->getRenderer());
	t->loadFont("by Nuria Bango", app_->getFont("PAINT22"), { 0, 0, 0, 255 });
	int w, h;
	app_->getFont("PAINT22")->getSizeOfText("by Nuria Bango", w, h);
	t->render({ WIN_WIDTH - w - 20, WIN_HEIGHT - h - 10, w, h });

	delete t;
	t = nullptr;

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