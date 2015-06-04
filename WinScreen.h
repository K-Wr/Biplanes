#pragma once
#include "Scene.h"
#include "ButtonPanel.h"
class WinScreen :
	public Scene
{
public:
	WinScreen(sf::RenderWindow& _window, MoveManager& _background, const Scene::ExitAction currentMode, int winnerNo);
	const Scene::ExitAction run() override;
	~WinScreen();
protected:
	void render() override;
	const Scene::ExitAction processEvents() override;
private:
	std::shared_ptr<ButtonPanel> buttonPanel;
	MoveManager& background;
};

