#pragma once
#include "MovingObject.h"
#include "BackgroundRectangle.h"
#include "Header.h"
class MenuBackground :
	public MovingObject
{
public:
	enum class Type{ Vertical, Horizontal, Both};
	enum class Direction{ Right, Left, Down, Up};
	MenuBackground();
	MenuBackground(const Type type, const Direction direction);
	void move(const sf::Int32 time) override;
	const bool exists() override { return true; }
	void draw(sf::RenderWindow& window) override;
	~MenuBackground();
private:
	Direction direction;
	std::vector<BackgroundRectangle> rectangles;
};

