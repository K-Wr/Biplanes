#pragma once
#include "Scene.h"
#include "ButtonPanel.h"
class PauseMenu :
	public Scene
{
public:
	PauseMenu(sf::RenderWindow& _window, MoveManager& _background, const Scene::ExitAction currentMode);
	~PauseMenu();
	const Scene::ExitAction run() override;
protected:
	void render() override;
	const Scene::ExitAction processEvents() override;
private:
	std::shared_ptr<ButtonPanel> buttonPanel;
	MoveManager& background;
};

