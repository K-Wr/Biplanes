#include "MoveManager.h"


MoveManager::MoveManager(sf::RenderWindow& wnd) : window(wnd), locked(false){
}
void MoveManager::add(std::shared_ptr<MovingObject> ob){
	objects.push_back(ob);
}
void MoveManager::add(MovingObject* ptr){
	objects.push_back(std::shared_ptr<MovingObject>(ptr));
}
void MoveManager::restart(){
	timer.restart();
}
void MoveManager::freeze(){
	locked = true;
}
void MoveManager::unfreeze(){
	locked = false;
	timer.restart();
}
//TODO: IMPROVE DELETEtING ELEMENTS
void MoveManager::move(){
	if (!locked){
		while (!(*objects.begin())->exists() && objects.begin() != objects.end())
			objects.erase(objects.begin());
		if (objects.begin() != objects.end())
			for (auto it = objects.begin() + 1; it != objects.end(); ++it){
			if (!(*it)->exists()){
				auto tempit = it - 1;
				objects.erase(it);
				it = tempit;
			}
			}

		sf::Int32 time = timer.getElapsedTime().asMilliseconds();
		timer.restart();
		for (auto& ob : objects){
			ob->move(time);
		}
	}
	for (auto& ob : objects){
		ob->draw(window);
	}
}
void MoveManager::clear(){
	objects.clear();
}
MoveManager::~MoveManager(){
	objects.clear();
}
