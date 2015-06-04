#include "PauseMenu.h"
#include "Game.h"
#include "StaticObject.h"
PauseMenu::PauseMenu(sf::RenderWindow& _window, MoveManager& _background, const Scene::ExitAction currentMode) : Scene(_window)
	, background(_background)
	, buttonPanel(new ButtonPanel({ std::shared_ptr<Button>(new Button("Back", Scene::ExitAction::GoBack, { 1066.f / 2.f, 250.f }, { 1.f, 0.f }, { 1066.f / 2.f, 300.f }))
		, std::shared_ptr<Button>(new Button("Restart", currentMode, { 1066.f / 2.f, 370.f }, { 0.f, 0.f }, { 1066.f / 2, 450.f })) 
		, std::shared_ptr<Button>(new Button("Main Menu", Scene::ExitAction::RunMainMenu, { 1066.f / 2.f, 490.f }, { 0.f, 0.f }, { 1066.f / 2, 600.f })) 
				})){
	background.freeze();
	sf::Text* text = new sf::Text("Pause", Game::getFont(), static_cast<unsigned>(80.f * SVector2f::getConversation().y));
	text->setPosition(SVector2f{ 600.f, 100.f });
	sf::RectangleShape* backgroundAlpha = new sf::RectangleShape(SVector2f{ 1366.f, 768.f });
	backgroundAlpha->setFillColor({ 0, 0, 0, 200 });
	backgroundAlpha->setPosition(SVector2f{ 0.f, 0.f });

	manager.add(new StaticObject(backgroundAlpha));
	manager.add(buttonPanel);
	manager.add(new StaticObject(text));
}
const Scene::ExitAction PauseMenu::run(){
	manager.restart();
	while (window.isOpen()){
		Scene::ExitAction act = processEvents();
		if (act != Scene::ExitAction::NoAction){
			if (act == Scene::ExitAction::GoBack){
				background.unfreeze();
				return Scene::ExitAction::NoAction;
			}
			return act;
		}
		render();
	}
	return Scene::ExitAction::Exit;
}
void PauseMenu::render(){
	window.clear();
	background.move();
	manager.move();
	window.display();
}
const Scene::ExitAction PauseMenu::processEvents(){
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			return Scene::ExitAction::Exit;
		}
		else if (event.type == sf::Event::KeyReleased){
			switch (event.key.code){
			case sf::Keyboard::S:
			case sf::Keyboard::Down:
				buttonPanel->selectNext();
				break;
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				buttonPanel->selectPrevious();
				break;
			case sf::Keyboard::Return:
				return buttonPanel->choose();
			}
		}
	}
	return Scene::ExitAction::NoAction;
}
PauseMenu::~PauseMenu(){

}
