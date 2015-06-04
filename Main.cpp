#include "Game.h"
#include "Header.h"





#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
int main()
{
	try{
		Log::open();
		Game game;
		game.run();
		Log::close();
	}
	catch (GameException& e){
		Log::close();
		std::cout << e.text << " error occured in " << e.source << std::endl;
		system("pause << void");
		return -1;
	}
	return 0;
}