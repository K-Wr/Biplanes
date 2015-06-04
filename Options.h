#pragma once
#include "Scene.h"
#include "Header.h"
#include "Settings.h"
#include "ButtonPanel.h"
class Options :
	public Scene
{
public:
	Options(sf::RenderWindow& window, Settings& settings);
	~Options();
	const Scene::ExitAction run();
protected:
	
	void render();
	const Scene::ExitAction processEvents();
private:
	std::vector<sf::Vector2u> availableResolutions;
	void loadResolutions();
	void setResolutionText(const sf::Vector2u& resolution);
	int selectedResolutionNo;
	std::shared_ptr<sf::Text> resolution;
	std::shared_ptr<sf::Text> difficulty;
	std::shared_ptr<sf::Text> screenMode;
	std::shared_ptr<ButtonPanel> buttons;
	std::shared_ptr<sf::Text> warning;
	Settings& usedSettings;
	Settings tempSettings;
	void updateDifficultyText();
	void nextDifficulty();
	void nextScreenMode();
	void nextResolution();
};

