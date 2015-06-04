#include "Battle.h"
#include "StaticObject.h"
#include "SVector2.h"
#include "TextureManager.h"
#include "WinScreen.h"
#include "Ground.h"
#include "Sky.h"
#include "PauseMenu.h"
Battle::Battle(sf::RenderWindow& window, const Battle::Mode _mode) : Scene(window), mode(_mode)
	, leftPlane(new Biplane(TextureManager::getTexture(TextureManager::TextureName::GreenBiplane), Biplane::StartPosition::Left))
	, rightPlane(new Biplane(TextureManager::getTexture(TextureManager::TextureName::RedBiplane), Biplane::StartPosition::Right)){
	addRandomBackground();
	collider.add(leftPlane);
	collider.add(rightPlane);
	collider.add(new Sky());
	manager.add(leftPlane);
	manager.add(rightPlane);

}
const Scene::ExitAction Battle::run(){
	timer.restart();
	sf::Clock collisionTimer;
	collisionTimer.restart();
	while (window.isOpen()){
		if (collisionTimer.getElapsedTime().asMilliseconds() > 30){
			collider.collide();
			collisionTimer.restart();
		}
		const Scene::ExitAction act = processEvents();
		if (act != Scene::ExitAction::NoAction){
			return act;
		}
		if (!leftPlane->exists()){
			return WinScreen(window, manager, (mode == Mode::VsAI) ? Scene::ExitAction::RunGameVsAI : Scene::ExitAction::RunGameVsPlayer, 2).run();
		}
		if (!rightPlane->exists()){
			return WinScreen(window, manager, (mode == Mode::VsAI) ? Scene::ExitAction::RunGameVsAI : Scene::ExitAction::RunGameVsPlayer, 1).run();
		}
		render();
	}
	return Scene::ExitAction::Exit;
}
void Battle::render(){
	window.clear();
	manager.move();
	window.display(); 
}
const Scene::ExitAction Battle::processEvents(){
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			return Scene::ExitAction::Exit;
		}
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape){
			return PauseMenu(window, manager, (mode == Mode::VsAI) ? Scene::ExitAction::RunGameVsAI : Scene::ExitAction::RunGameVsPlayer).run();
		}
	}
	sf::Int32 time = timer.getElapsedTime().asMilliseconds();
	leftPlayerTurn(time);
	rightPlayerTurn(time);
	timer.restart();
	return Scene::ExitAction::NoAction;
}
void Battle::leftPlayerTurn(const sf::Int32 time){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		leftPlane->changeSpeed(Up, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		leftPlane->changeSpeed(Down, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		leftPlane->changeSpeed(Left, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		leftPlane->changeSpeed(Right, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		auto bullet = leftPlane->fireBullet();
		if (bullet){
			manager.add(bullet);
			collider.add(bullet);
		}
	}
}
Battle::~Battle(){
}
void Battle::addRandomBackground(){
	sf::RectangleShape* backgroundSky = new sf::RectangleShape(SVector2f(1366.f, 668.f));
	backgroundSky->setTexture(TextureManager::getTexture(TextureManager::TextureName::Sky));
	backgroundSky->setPosition(0.f, 0.f);
	sf::RectangleShape* backgroundGround = new sf::RectangleShape(SVector2f(1366.f, 100.f));
	backgroundGround->setPosition(SVector2f(0.f, 668.f));
	TextureManager::TextureName textureName;
	switch (rand() % 6){
	case 0:
		textureName = TextureManager::TextureName::GrassGround1;
		break;
	case 1:
		textureName = TextureManager::TextureName::GrassGround2;
		break;
	case 2:
		textureName = TextureManager::TextureName::GrassGround3;
		break;
	case 3:
		textureName = TextureManager::TextureName::DirtGround;
		break;
	case 4:
		textureName = TextureManager::TextureName::SandGround1;
		break;
	case 5:
		textureName = TextureManager::TextureName::SandGround2;
		break;
	}
	
	backgroundGround->setTexture(TextureManager::getTexture(textureName));
	std::shared_ptr<Ground> ground(new Ground(std::shared_ptr<sf::Drawable>(backgroundGround), backgroundGround->getGlobalBounds()));
	manager.add(new StaticObject(backgroundSky));
	manager.add(ground);
	collider.add(ground);
}