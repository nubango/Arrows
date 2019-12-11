// Grupo 23, Nuria Bango Iglesias

#include "checkML.h"
#include "SDLApp.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	try {
		SDLApp game;
		game.run();
	}
	catch (std::string & error) {
		std::cout << error << std::endl;
	}
	return 0;
}