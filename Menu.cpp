#include "Menu.h"
#include "MenuBackground.h"
#include "ButtonPanel.h"
#include "StaticObject.h"
#include "Game.h"
Menu::Menu(sf::RenderWindow& win) 
	: Scene(win)
	, buttons(new ButtonPanel({
	std::shared_ptr<Button>(new Button("New game", Scene::ExitAction::RunPlayModeSelect, { 0.f, 300.f }, { 1.f, 0.f }, { 1066.f / 2.f, 300.f }))
	, std::shared_ptr<Button>(new Button("Options", Scene::ExitAction::RunOptions, { -300.f, 400.f }, { 1.f, 0.f }, { 1066.f / 2.f, 400.f }))
	, std::shared_ptr<Button>(new Button("About", Scene::ExitAction::RunAbout, { -600.f, 500.f }, { 1.f, 0.f }, { 1066.f / 2.f, 500.f }))
	, std::shared_ptr<Button>(new Button("Exit", Scene::ExitAction::Exit, { -900.f, 600.f }, { 1.f, 0.f }, {1066.f / 2, 600.f }))
								})){
	sf::Text* text = new sf::Text("BIPLANES", Game::getFont(), static_cast<unsigned>(72.f * SVector2f::getConversation().y));
	text->setPosition(SVector2f(520.f, 100.f));
	
	manager.add(new MenuBackground());
	manager.add(buttons);
	manager.add(new StaticObject(text));
}
const Menu::ExitAction Menu::run(){
	
	manager.restart();
	while (window.isOpen()){
		Scene::ExitAction act = processEvents();
		if (act != Scene::ExitAction::NoAction){
			return act;
		}
		render();
	}
	return Scene::ExitAction::Exit;
}
void Menu::render(){
	window.clear();
	manager.move();
	window.display();
}
const Scene::ExitAction Menu::processEvents(){
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			return Scene::ExitAction::Exit;
		}
		else if (event.type == sf::Event::KeyReleased){
			switch (event.key.code){
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				buttons->selectPrevious();
				break;
			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				buttons->selectNext();
				break;
			case sf::Keyboard::Return:
			case sf::Keyboard::D:
			case sf::Keyboard::Right:
				return buttons->choose();
			case sf::Keyboard::Escape:
				return Scene::ExitAction::Exit;
			}
		}
	}
	return Scene::ExitAction::NoAction;
}