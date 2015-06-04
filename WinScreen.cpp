#include "WinScreen.h"
#include "Game.h"
#include "SVector2.h"
#include "StaticObject.h"
WinScreen::WinScreen(sf::RenderWindow& _window, MoveManager& _background, const Scene::ExitAction currentMode, int winnerNo) : Scene(_window)
		, background(_background)
		, buttonPanel(new ButtonPanel({ std::shared_ptr<Button>(new Button("Play again", currentMode, { -500.f, 300.f }, { 1.f, 0.f }, { 1066.f / 2.f, 300.f }))
		, std::shared_ptr<Button>(new Button("Exit", Scene::ExitAction::RunMainMenu, { -750.f, 500.f }, { 1.f, 0.f }, { 1066.f / 2, 500.f })) })){
	background.freeze();
	sf::Text* text = new sf::Text(std::string("Player ") + std::to_string(winnerNo) + " wins", Game::getFont(), static_cast<unsigned>(80.f * SVector2f::getConversation().y));
	text->setPosition(SVector2f{500.f, 100.f});
	sf::RectangleShape* backgroundAlpha = new sf::RectangleShape(SVector2f{1366.f, 768.f});
	backgroundAlpha->setFillColor({ 0, 0, 0, 200 });
	backgroundAlpha->setPosition(SVector2f{0.f, 0.f});

	manager.add(new StaticObject(backgroundAlpha));
	manager.add(buttonPanel);
	manager.add(new StaticObject(text));
}
const Scene::ExitAction WinScreen::run(){
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
void WinScreen::render(){
	window.clear();
	background.move();
	manager.move();
	window.display();
}
const Scene::ExitAction WinScreen::processEvents(){
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
WinScreen::~WinScreen()
{
}
