#include "EndState.h"

#include "SDLApp.h" 

void EndState::renderMessage() const
{
	Texture* t = new Texture(app_->getRenderer());
	int w, h;

	t->loadFont("GAME OVER", app_->getFont("PAINT72"), { 0, 0, 0, 255 });
	app_->getFont("PAINT72")->getSizeOfText("GAME OVER", w, h);

	t->render({ (WIN_WIDTH - w) / 2, WIN_HEIGHT / 2 + 50, w, h });

	if (win_)
	{
		t->loadFont("YOU WIN!", app_->getFont("PAINT72"), { 0, 0, 0, 255 });
		app_->getFont("PAINT72")->getSizeOfText("YOU WIN!", w, h);
	}
	else
	{
		t->loadFont("YOU LOSE", app_->getFont("PAINT72"), { 0, 0, 0, 255 });
		app_->getFont("PAINT72")->getSizeOfText("YOU LOSE", w, h);
	}

	t->render({ (WIN_WIDTH - w) / 2, WIN_HEIGHT / 2 + 100 , w, h });

	delete t;
	t = nullptr;
}

EndState::EndState(SDLApp* app, bool end, int score) :
	GameState(app), win_(end)
{
	MenuButton* button = new MenuButton({ 400, 550 }, BUTTON_WIDTH, BUTTON_HEIGHT, app_->getTexture("MENU"), this, SDLApp::toMenu);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ 680, 550 }, BUTTON_WIDTH, BUTTON_HEIGHT, app_->getTexture("EXIT"), this, SDLApp::quitApp);
	addEventHandler(button);
	addGameObject(button);

	leadBoard_ = new LeaderBoard(app_, "top10.txt");
	if (win_)
	{
		std::cout << "ENTER YOUR NAME: ";
		std::string name;
		std::cin >> name;
		leadBoard_->addScore(name, score);
		leadBoard_->save("top10.txt");
	}
}

EndState::~EndState()
{
	delete leadBoard_;
	leadBoard_ = nullptr;
}

void EndState::render() const
{
	app_->getTexture("BACKGROUND_SPRING")->render({ 0,0,WIN_WIDTH,WIN_HEIGHT });

	app_->getTexture("PANEL")->render({ (WIN_WIDTH / 2) - 165, 20, 330, 350 });


	leadBoard_->render();

	renderMessage();

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
