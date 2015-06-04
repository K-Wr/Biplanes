#include "Options.h"
#include "MenuBackground.h"
#include "Game.h"
#include "StaticObject.h"
Options::Options(sf::RenderWindow& window, Settings& settings)
	: Scene(window), tempSettings(settings), usedSettings(settings), selectedResolutionNo(-1)
	, resolution(new sf::Text("", Game::getFont(), static_cast<unsigned>(50 * SVector2f::getConversation().y)))
	, difficulty(new sf::Text("", Game::getFont(), static_cast<unsigned>(50 * SVector2f::getConversation().y)))
	, screenMode(new sf::Text((settings.screenMode == Settings::ScreenMode::fullscreen) ? "Fullscreen" : "Windowed"
							, Game::getFont(), static_cast<unsigned>(Game::getFont(), 50.f * SVector2f::getConversation().y)))
	, warning(new sf::Text("You should restart\nthe game for changes\nto take effect", Game::getFont(), 50))
	, buttons(new ButtonPanel({
	std::shared_ptr<Button>(new Button("Resolution:", Scene::ExitAction::ChangeResolution, { -300.f, 200.f }, { 1.f, 0.f }, { 100.f, 200.f }))
	, std::shared_ptr<Button>(new Button("Difficulty:", Scene::ExitAction::ChangeDifficutlty, { -300.f, 350.f }, { 1.f, 0.f }, { 100.f, 350.f }))
	, std::shared_ptr<Button>(new Button("Screen mode:", Scene::ExitAction::ChangeScreenMode, { -300.f, 500.f }, { 1.f, 0.f }, { 100.f, 500.f }))
	, std::shared_ptr<Button>(new Button("Save", Scene::ExitAction::Save, { -500.f, 650.f }, { -1.f, 0.f }, { 200.f, 650.f }))
	, std::shared_ptr<Button>(new Button("Back", Scene::ExitAction::RunMainMenu, { 1466.f, 650.f }, { 1.f, 0.f }, { 866.f, 650.f }))
	 })){
	setResolutionText(settings.windowSize);
	loadResolutions();
	updateDifficultyText();
	manager.add(new MenuBackground());
	sf::Text* text = new sf::Text("Options", Game::getFont(), static_cast<unsigned>(80.f * SVector2f::getConversation().y));
	text->setPosition(SVector2f(540.f, 40.f));
	warning->setPosition(SVector2f(900.f, 230.f));
	warning->setColor({0,0,0,0});
	manager.add(new StaticObject(warning));
	manager.add(buttons);
	manager.add(new StaticObject(text));
	resolution->setPosition(SVector2f{600.f, 210.f});
	difficulty->setPosition(SVector2f{600.f, 360.f});
	screenMode->setPosition(SVector2f{600.f, 510.f});
	manager.add(new StaticObject(difficulty));
	manager.add(new StaticObject(resolution));
	manager.add(new StaticObject(screenMode));
}
void Options::render(){
	window.clear();
	manager.move();
	window.display();
}
void Options::loadResolutions(){
	std::ifstream stream("resolutions");
	if (!stream)
		throw GameException("Error openning resolutions file", "Options::loadResolutions()");
	while (!stream.eof()){
		sf::Vector2u resolution;
		stream >> resolution.x;
		stream >> resolution.y;
		availableResolutions.push_back(resolution);
	}
	stream.close();
}
void Options::setResolutionText(const sf::Vector2u& resolutionToSet){
	resolution->setString(std::to_string(resolutionToSet.x) + " x " + std::to_string(resolutionToSet.y));
}
const Scene::ExitAction Options::run(){
	while (window.isOpen()){
		Scene::ExitAction act = processEvents();
		if (act != Scene::ExitAction::NoAction){
			return act;
		}
		render();
	}
	return Scene::ExitAction::Exit;
}
void Options::nextDifficulty(){
	switch (tempSettings.difficulty){
	case Settings::Difficulty::death:
		tempSettings.difficulty = Settings::Difficulty::easy;
		break;
	case Settings::Difficulty::easy:
		tempSettings.difficulty = Settings::Difficulty::medium;
		break;
	case Settings::Difficulty::medium:
		tempSettings.difficulty = Settings::Difficulty::hard;
		break;
	case Settings::Difficulty::hard:
		tempSettings.difficulty = Settings::Difficulty::death;
		break;
	}
	updateDifficultyText();
}
void Options::nextResolution(){
	selectedResolutionNo++;
	if (selectedResolutionNo == availableResolutions.size()){
		selectedResolutionNo = 0;
	}
	tempSettings.windowSize = availableResolutions[selectedResolutionNo];
	setResolutionText(tempSettings.windowSize);
}

const Scene::ExitAction Options::processEvents(){
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::KeyReleased){
			switch (event.key.code){
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
			case sf::Keyboard::Left:
			case sf::Keyboard::A:
				buttons->selectPrevious();
				break;
			case sf::Keyboard::Down:
			case sf::Keyboard::S:
			case sf::Keyboard::Right:
			case sf::Keyboard::D:
				buttons->selectNext();
				break;
			case sf::Keyboard::Escape:
				return Scene::ExitAction::RunMainMenu;
				break;
			case sf::Keyboard::Return:
			case sf::Keyboard::Space:
				
				switch (buttons->choose()){
				case Scene::ExitAction::Save:
					usedSettings.set(tempSettings);
				case Scene::ExitAction::RunMainMenu:
					return Scene::ExitAction::RunMainMenu;
					break;
				case Scene::ExitAction::ChangeDifficutlty:
					nextDifficulty();
					break;
				case Scene::ExitAction::ChangeResolution:
					nextResolution();
					warning->setColor({ 255, 255, 0 });
					break;
				case Scene::ExitAction::ChangeScreenMode:
					nextScreenMode();
					warning->setColor({ 255, 255, 0 });
					break;
				}
				break;
			}
		}
	}
	return Scene::ExitAction::NoAction;
}
void Options::nextScreenMode(){
	if (tempSettings.screenMode == Settings::ScreenMode::fullscreen){
		tempSettings.screenMode = Settings::ScreenMode::windowed;
		screenMode->setString("Windowed");
		
	}
	else{
		tempSettings.screenMode = Settings::ScreenMode::fullscreen;
		screenMode->setString("Fullscreen");
	}
}
void Options::updateDifficultyText(){
	switch (tempSettings.difficulty)
	{
	case Settings::Difficulty::easy:
		difficulty->setString("Easy");
		break;
	case Settings::Difficulty::medium:
		difficulty->setString("Medium");
		break;
	case Settings::Difficulty::hard:
		difficulty->setString("Hard");
		break;
	case Settings::Difficulty::death:
		difficulty->setString("Death");
		break;
	}
}
Options::~Options()
{
}
