#include "CollisionManager.h"


CollisionManager::CollisionManager(){
}
void CollisionManager::collide(){
	for (auto i = objects.begin(); i != objects.end(); ++i){
		for (auto j = i + 1; j != objects.end(); ++j){
			if ((*i)->getBounds().intersects((*j)->getBounds())){
				(*i)->collide((*j)->getWeight());
				(*j)->collide((*i)->getWeight());
			}
		}
	}
	while (objects.begin() != objects.end() && !(*objects.begin())->exists())
		objects.erase(objects.begin());
	if (objects.begin() != objects.end())
		for (auto it = objects.begin() + 1; it != objects.end(); ++it){
			if (!(*it)->exists()){
				auto tempit = it - 1;
				objects.erase(it);
				it = tempit;
			}
		}
}
void CollisionManager::add(std::shared_ptr<CollidingObject> a){
	objects.push_back(a);
}
void CollisionManager::add(CollidingObject* a){
	objects.push_back(std::shared_ptr<CollidingObject>(a));
}
CollisionManager::~CollisionManager(){
}
