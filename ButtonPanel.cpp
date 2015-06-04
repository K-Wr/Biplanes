#include "ButtonPanel.h"


ButtonPanel::ButtonPanel(std::initializer_list<std::shared_ptr<Button>> _buttons) 
	: buttons(_buttons)
	, selected(0)
	, capacity(buttons.size()){
	buttons[0]->select();
}
void ButtonPanel::move(const sf::Int32 time){
	for (auto& btn : buttons){
		btn->move(time);
	}
}
std::shared_ptr<Button> ButtonPanel::getByAction(const Scene::ExitAction& action){
	for (auto& button : buttons){
		if (button->press() == action){
			return button;
		}
	}
	throw GameException("No appropriate button found", "ButtonPanel::getByAction()");
}
void ButtonPanel::draw(sf::RenderWindow& window){
	for (auto& btn : buttons){
		btn->draw(window);
	}
}
void ButtonPanel::selectNext(){
	buttons[selected]->unselect();
	selected++;
	if (selected == capacity){
		selected = 0;
	}
	buttons[selected]->select();

}
void ButtonPanel::selectPrevious(){
	buttons[selected]->unselect();
	selected--;
	if (selected == -1){
		selected = capacity - 1;
	}
	buttons[selected]->select();
}
const Scene::ExitAction ButtonPanel::choose(){
	return buttons[selected]->press();
}
ButtonPanel::~ButtonPanel()
{
}
