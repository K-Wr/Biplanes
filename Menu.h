#pragma once
#include "Scene.h"
#include "ButtonPanel.h"
class Menu : public Scene
{
public:
	Menu(sf::RenderWindow& win);
	const ExitAction run() override;
	~Menu(){}
protected:
	void render() override;
	const Scene::ExitAction processEvents() override;
private:
	std::shared_ptr<ButtonPanel> buttons;
};

