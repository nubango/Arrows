#include "SDLApp.h"

#include "GameState.h"

SDLApp::SDLApp() :
	exit_(false)
{
	// Se inicializa SDL
	int e = SDL_Init(SDL_INIT_EVERYTHING);
	if (e > 0) throw SDLError(SDL_GetError());

	window_ = SDL_CreateWindow("Arrows 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window_) throw SDLError(SDL_GetError());
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer_) throw SDLError(SDL_GetError());

	// Se crean las texturas

	// Se crea la maquina de estados
	stateMachine_ = new GameStateMachine();
}

SDLApp::~SDLApp()
{
	// Se borra la maquina de estados
	delete stateMachine_;
	stateMachine_ = nullptr;

	// Se borran las texturas

	// Se borran atributos de SDL
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void SDLApp::run()
{
	while (!exit_)
	{
		handleEvents();
		stateMachine_->currentState()->update();
		render();
	}
}

void SDLApp::render() const
{
	SDL_RenderClear(renderer_);
	stateMachine_->currentState()->render();
	SDL_RenderPresent(renderer_);
}

void SDLApp::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit_)
	{
		stateMachine_->currentState()->handleEvent(event);
		if (event.type == SDL_QUIT)
		{
			exit_ = true;
		}
	}
}