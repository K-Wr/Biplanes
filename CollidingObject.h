#pragma once
#include "Header.h"
class CollidingObject{
public:
	enum class Weight{ Ground, Bullet, Biplane, Sky };
	CollidingObject(Weight _weight) : weight(_weight){

	}
	virtual const sf::FloatRect getBounds() = 0;
	virtual const bool exists() = 0;
	virtual void collide(const Weight w) = 0;
	const Weight getWeight() {
		return weight;
	}
private:
	Weight weight;
	
};