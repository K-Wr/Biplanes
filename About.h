#pragma once
#include "Scene.h"
class About :
	public Scene
{
public:
	About(sf::RenderWindow& window);
	const ExitAction run();
	~About();
protected:
	const ExitAction processEvents();
	void render();
};

