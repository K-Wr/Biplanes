#pragma once
#include "CollidingObject.h"
#include "SRect.h"
class Sky : public CollidingObject{
public:
	Sky() : CollidingObject(CollidingObject::Weight::Sky), bounds(SFloatRect(-100.f,-50.f, 1500.f, -2000.f)){}
	const sf::FloatRect getBounds() override{
		return bounds;
	}
	const bool exists() override{
		return true;
	}
	void collide(const Weight w) override{
	}
private:
	const sf::FloatRect bounds;
};