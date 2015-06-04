#pragma once
#include "MovingObject.h"
class StaticObject :
	public MovingObject
{
public:
	StaticObject(std::shared_ptr<sf::Drawable> _drawable) : drawable(_drawable){
	}
	StaticObject(sf::Drawable* _drawable) :drawable(_drawable){

	}
	void draw(sf::RenderWindow& window){
		window.draw(*drawable);
	}
	virtual const bool exists()override{
		return true;
	}
	void move(const sf::Int32 time)override {
	}
	~StaticObject(){};
private:
	std::shared_ptr<sf::Drawable> drawable;
};

