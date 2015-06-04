#include "PlayModeSelect.h"
#include "MenuBackground.h"

PlayModeSelect::PlayModeSelect(sf::RenderWindow& window) : Scene(window), buttons(new ButtonPanel({
	std::shared_ptr<Button>(new Button("Player Vs AI", Scene::ExitAction::RunGameVsAI, {-450.f, 100.f}, {3.f, 0.f}, {458.f, 100.f}, 1.5f)),
	std::shared_ptr<Button>(new Button("Player vs Player", Scene::ExitAction::RunGameVsPlayer, { -450.f, 300.f }, { 3.f, 0.f }, { 458.f, 300.f }, 1.5f)),
	std::shared_ptr<Button>(new Button("Back", Scene::ExitAction::RunMainMenu, { -450.f, 650.f }, { 3.f, 0.f }, { 458.f, 650.f }, 1.5f)),
	})){
	manager.add(new MenuBackground());
	manager.add(buttons);

}

const Scene::ExitAction PlayModeSelect::run(){
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
void PlayModeSelect::render(){
	window.clear();
	manager.move();
	window.display();
}
const Scene::ExitAction PlayModeSelect::processEvents(){
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			return Scene::ExitAction::Exit;
		}
		else if (event.type == sf::Event::KeyReleased){
			switch (event.key.code){
			case sf::Keyboard::Escape:
			case sf::Keyboard::A:
			case sf::Keyboard::Left:
				return Scene::ExitAction::RunMainMenu;
			case sf::Keyboard::Return:
			case sf::Keyboard::D:
			case sf::Keyboard::Right:
				return buttons->choose();
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
				buttons->selectPrevious();
				break;
			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				buttons->selectNext();
				break;
			}
		}
	}
	return Scene::ExitAction::NoAction;
}