#include "About.h"
#include "MenuBackground.h"
#include "Game.h"
#include "StaticObject.h"
#include "SVector2.h"
About::About(sf::RenderWindow& window) : Scene(window){
	manager.add(new MenuBackground());
	sf::Text* about = new sf::Text("About", Game::getFont(), static_cast<unsigned>(SVector2f::getConversation().y * 70.f));
	sf::Text* howToPlay = new sf::Text("HOW TO PLAY:\n"
		"    - Press W A S D(Player 1) or arrow keys(Player 2) to move.\n"
		"    - To begin to fly you should gain enough speed first.\n"
		"    - Press Space(Player 1) or right Ctrl(Player 2) to fire.\n"
		"        DO NOT touch the ground! It might be lethal. \n                 And DO NOT fly too high (that can be lethal, too).\n\n"

		"КАК ИГРАТЬ:\n"
		"    - Нажмайте Ц Ф Ы В(Игрок 1) или на стрелки(Игрок 2), чтобы летать.\n"
		"    - Для того, чтобы взлететь, сначала необходимо набрать скорость.\n"
		"    - Нажимайте на Пробел(Игрок 1) или на правый Ctrl(Игрок 2),\n                                             "
		"                                 чтобы стрелять.\n"
		"        НЕ касайтесь земли, это может быть смертельно.\n                 Также НЕ залетайте слишком высоко(это тоже смертельно).\n"
		, Game::getFont(), static_cast<unsigned>(SVector2f::getConversation().y * 30.f));
	sf::Text* author = new sf::Text("Developer: Kravchenko Viktor\n       Minsk, 2014"
		, Game::getFont(), static_cast<unsigned>(SVector2f::getConversation().y *  20.f));
	author->setPosition(SVector2f{1000.f, 700.f});
	about->setPosition(SVector2f{570.f, 50.f});
	howToPlay->setPosition(SVector2f{100.f, 180.f});
	manager.add(new StaticObject(about));
	manager.add(new StaticObject(howToPlay));
	manager.add(new StaticObject(author));
}
const Scene::ExitAction About::run(){
	while (window.isOpen()){
		render();
		const ExitAction act = processEvents();
		if (act != Scene::ExitAction::NoAction){
			return act;
		}
	}
	return ExitAction::Exit;
}
void About::render(){
	window.clear();
	manager.move();
	window.display();
}
const Scene::ExitAction About::processEvents(){
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::KeyReleased){
			if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape 
				|| event.key.code == sf::Keyboard::Space){
				return Scene::ExitAction::RunMainMenu;
			}
		}
	}
	return Scene::ExitAction::NoAction;
}
About::~About()
{
}
