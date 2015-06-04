#pragma once
#include "Scene.h"
#include "ButtonPanel.h"
class PlayModeSelect : public Scene
{
public:
	PlayModeSelect(sf::RenderWindow& window);
	~PlayModeSelect(){

	}
	const Scene::ExitAction run() override;
protected:
	void render() override;
	const Scene::ExitAction processEvents() override;
private:
	std::shared_ptr<ButtonPanel> buttons;
};

