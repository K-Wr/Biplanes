#pragma once
#include "CollidingObject.h"
#include "Header.h"
class CollisionManager
{
public:
	CollisionManager();
	void add(std::shared_ptr<CollidingObject> obj);
	void add(CollidingObject* obj);
	void collide();
	~CollisionManager();
private:
	std::vector<std::shared_ptr<CollidingObject>> objects;
};

