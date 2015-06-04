#pragma once
#include "Header.h"
class MovingObject
{
public:
	MovingObject(){};
	virtual void draw(sf::RenderWindow&) = 0;
	virtual const bool exists() = 0;
	virtual void move(const sf::Int32 time) = 0;
	virtual ~MovingObject(){};
};

