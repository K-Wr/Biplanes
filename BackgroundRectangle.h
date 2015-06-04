#pragma once
#include "MovingObject.h"
#include "SVector2.h"
#include "SRect.h"
class BackgroundRectangle :
	public MovingObject
{
public:
	BackgroundRectangle(const SVector2f size, const SVector2f start_position, const SVector2f speed);
	void move(const sf::Int32 time) override;
	const SFloatRect getPosition();
	void setPosition(const SVector2f& position);
	const bool exists() override { return true; }
	void draw(sf::RenderWindow& window) override;
	void setRandomDarkColor();
	~BackgroundRectangle();
private: 
	
	sf::Vector2f speed;
	sf::RectangleShape shape;
};

