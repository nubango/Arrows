#include "SDLApp.h"

GameStateMachine* SDLApp::stateMachine_ = nullptr;
bool SDLApp::exit_ = false;

void SDLApp::loadTextures()
{
	std::ifstream file;
	file.open(TEXTURES_FILE_NAME);

	if (!file.is_open())
		throw FileNotFoundError("Couldn't open " + TEXTURES_FILE_NAME + ".txt\n");

	int numTextures;
	file >> numTextures;

	for (int i = 0; i < numTextures; i++)
	{
		std::string name;
		std::string path;
		int row;
		int col;
		file >> name >> path >> row >> col;

		// Se rellena el diccionario
		textures_[name] = new Texture(renderer_);
		textures_[name]->load(IMAGES_PATH + path, row, col);
	}

	file.close();
}

void SDLApp::loadFonts()
{
	std::ifstream file;
	file.open(FONTS_FILE_NAME);

	if (!file.is_open())
		throw FileNotFoundError("Couldn't open " + FONTS_FILE_NAME + ".txt\n");

	int numFonts;
	file >> numFonts;

	for (int i = 0; i < numFonts; i++)
	{
		std::string name;
		std::string path;
		int size;
		file >> name >> path >> size;

		// Se rellena el diccionario
		fonts_[name] = new Font();
		fonts_[name]->load(FONTS_PATH + path, size);
	}

	file.close();
}

SDLApp::SDLApp()
{
	// Se inicializa SDL
	int e = SDL_Init(SDL_INIT_EVERYTHING);
	if (e > 0) throw SDLError(SDL_GetError());

	window_ = SDL_CreateWindow("Arrows 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window_) throw SDLError(SDL_GetError());
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer_) throw SDLError(SDL_GetError());

	// Se inicializa TTF
	TTF_Init();

	// Se crean las texturas
	loadTextures();
	loadFonts();

	// Se crea la maquina de estados
	stateMachine_ = new GameStateMachine();
	stateMachine_->pushState(new MainMenuState(this));
}

SDLApp::~SDLApp()
{
	// Se borra la maquina de estados
	delete stateMachine_;
	stateMachine_ = nullptr;

	// Se borran las texturas
	for (std::pair<std::string, Texture*> t : textures_)
	{
		delete t.second;
		t.second = nullptr;
	}
	textures_.clear();

	// Se borran las fuentes
	for (std::pair<std::string, Font*> f : fonts_)
	{
		delete f.second;
		f.second = nullptr;
	}
	fonts_.clear();

	TTF_Quit();

	// Se borran atributos de SDL
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void SDLApp::run()
{
	while (!exit_)
	{
		int startTime = SDL_GetTicks();
		handleEvents();
		update();
		render();
		int frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
	}
}

void SDLApp::render() const
{
	SDL_RenderClear(renderer_);
	stateMachine_->currentState()->render();
	SDL_RenderPresent(renderer_);
}

void SDLApp::update()
{
	stateMachine_->currentState()->update();
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

void SDLApp::quitApp(SDLApp* app)
{
	exit_ = true;
}

void SDLApp::resumeApp(SDLApp* app)
{
	stateMachine_->popState();
}

void SDLApp::loadPlayState(SDLApp* app)
{
	try {
		int code;
		std::cout << "Introduce tu codigo de carga: "; std::cin >> code;
		stateMachine_->pushState(new PlayState(app));
		static_cast<PlayState*>(stateMachine_->currentState())->loadFromFile(code);
	}
	catch (FileNotFoundError e)
	{
		toPlay(app);
	}
}

void SDLApp::savePlayState(SDLApp* app)
{
	int code;
	std::cout << "Introduce tu codigo de guardado: "; std::cin >> code;
	stateMachine_->popState();
	static_cast<PlayState*>(stateMachine_->currentState())->saveToFile(code);
}

void SDLApp::toPlay(SDLApp* app)
{
	stateMachine_->pushState(new PlayState(app));
}

void SDLApp::toPause(SDLApp* app)
{
	stateMachine_->pushState(new PauseState(app));
}

void SDLApp::toMenu(SDLApp* app)
{
	while (stateMachine_->currentState()->getStateName() != StateName::MENU_STATE)
		stateMachine_->popState();
}

void SDLApp::toEnd(SDLApp* app)
{
	bool end = static_cast<PlayState*>(stateMachine_->currentState())->hasWon();
	int score = static_cast<PlayState*>(stateMachine_->currentState())->getScore();

	stateMachine_->pushState(new EndState(app, end, score));
}