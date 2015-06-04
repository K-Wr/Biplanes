#pragma once
#include "Header.h"
#include "CollidingObject.h"
#include "StaticObject.h"
class Ground :
	public CollidingObject, public StaticObject
{
public:
	Ground(std::shared_ptr<sf::Drawable> _drawable, const sf::FloatRect& _bounds) : StaticObject(_drawable)
		, CollidingObject(CollidingObject::Weight::Ground), bounds(_bounds){
	}
	virtual const bool exists()override{
		return true;
	}
	const sf::FloatRect getBounds() override{
		return bounds;
	}
	void collide(const Weight w) override{
	}
	~Ground(){}
private:
	const sf::FloatRect bounds;
};

