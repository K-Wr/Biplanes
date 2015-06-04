#pragma once
#include "MovingObject.h"
#include "Button.h"
class ButtonPanel :
	public MovingObject
{
public:
	ButtonPanel(std::initializer_list<std::shared_ptr<Button>> init_list);
	const bool exists() override{
		return true;
	}
	void draw(sf::RenderWindow& window) override;
	void move(const sf::Int32 time) override;
	std::shared_ptr<Button> getByAction(const Scene::ExitAction& action);
	void selectNext();
	void selectPrevious();
	const Scene::ExitAction choose();
	~ButtonPanel();
private:
	std::vector<std::shared_ptr<Button>> buttons;
	int selected;
	unsigned capacity;
};

