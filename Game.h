#pragma once
#include "Header.h"
#include "Settings.h"
#include "Scene.h"
class Game
{
public:
	Game();
	void run();
	~Game();
	static const sf::Font& getFont();
private:
	static bool fontLoaded;
	static sf::Font font;
	Settings settings;
	Scene::ExitAction runScene(Scene::ExitAction act);
	sf::RenderWindow window;
	
};

