#ifndef _SDLAPP_H_
#define _SDLAPP_H_

#include "checkML.h"
#include "SDLError.h"
#include "GameStateMachine.h"
#include "FileNotFoundError.h"

#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

#include <fstream>
#include <map>

class SDLApp
{
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	static GameStateMachine* stateMachine_;

	static bool exit_;

	std::map<std::string, Texture*> textures_;

	// AUX: lee las texturas del archivo textures.txt
	void loadTextures();

public:
	SDLApp();
	~SDLApp();

	void run();
	void render() const;
	void update();
	void handleEvents();

	Texture* getTexture(std::string s) { return textures_.at(s); };

	// Metodos estaticos para los callbacks
	static void quitApp(SDLApp* app);
	static void resumeApp(SDLApp* app);
	static void loadPlayState(SDLApp* app);
	static void savePlayState(SDLApp* app);
	static void toPlay(SDLApp* app);
	static void toPause(SDLApp* app);
	static void toMenu(SDLApp* app);
	static void toEnd(SDLApp* app);
};

#endif // !_SDLAPP_H_