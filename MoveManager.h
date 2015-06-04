#pragma once
#include "MovingObject.h"
class MoveManager
{
public:
	MoveManager(sf::RenderWindow& win);
	void add(std::shared_ptr<MovingObject> ob);
	void add(MovingObject* ptr);
	void clear();
	void freeze();
	void unfreeze();
	void restart();
	void move();
	~MoveManager();
private:
	bool locked;
	sf::Clock timer;
	sf::RenderWindow& window;
	std::vector<std::shared_ptr<MovingObject>> objects;
};

