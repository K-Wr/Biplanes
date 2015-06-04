#include "MenuBackground.h"
#include "SRect.h"


MenuBackground::MenuBackground(){
	Type type;
	switch (rand() % 4){
	case 0: case 3: type = Type::Both;
		direction = (Direction)(rand() % 4);
		break;
	case 1: type = Type::Horizontal;
		direction = (rand() % 2) ? Direction::Down : Direction::Up;
		break;
	case 2: type = Type::Vertical;
		direction = (rand() % 2) ? Direction::Right : Direction::Left;
		break;
	}
	this->MenuBackground::MenuBackground(type, direction);
}
MenuBackground::MenuBackground(const MenuBackground::Type type, const MenuBackground::Direction dir) : direction(dir){
	
	SVector2f size, speed;
	const float linearSpeed = 0.1f;
	switch (dir){
	case MenuBackground::Direction::Down:
		speed = {0.f, linearSpeed};
		break;
	case MenuBackground::Direction::Up:
		speed = { 0.f, -linearSpeed };
		break;
	case MenuBackground::Direction::Left:
		speed = { linearSpeed, 0.f };
		break;
	case MenuBackground::Direction::Right:
		speed = { -linearSpeed, 0.f };
		break;
	}
	switch (type){
	case MenuBackground::Type::Vertical:
		size = { 78.f * 1.2f, 780.f };
		for (unsigned i = 0; i < 21; ++i){
			rectangles.push_back(BackgroundRectangle(size, SVector2f(78.f * static_cast<float>(i), 0.f ), speed));
		}
		break;
	case MenuBackground::Type::Horizontal:
		size = { 1370.f, 78.f * 1.2f };
		for (unsigned i = 0; i < 11; ++i){
			rectangles.push_back(BackgroundRectangle(size, SVector2f(0.f, 78.f * static_cast<float>(i)), speed));
		}
		break;
	case MenuBackground::Type::Both:
		size = { 78.f * 1.2f, 78.f * 1.2f };
		for (unsigned i = 0; i < 21; i++){
			for (unsigned j = 0; j < 11; ++j){
				rectangles.push_back(BackgroundRectangle(size, SVector2f(78.f * static_cast<float>(i)
					, 78.f * static_cast<float>(j)), speed));
			}
		}
		break;
	}
}
void MenuBackground::move(sf::Int32 time){
	for (auto& rect : rectangles){
			rect.move(time);
			const SFloatRect position = rect.getPosition();
			switch (direction){
			case Direction::Down:
				if (position.top > 768.f){
					rect.setPosition({ position.left, 0.f + position.top - 768.f - position.height });
					rect.setRandomDarkColor();
				}
				break;
			case Direction::Up:
				if (position.top + position.height < 0.f){
					rect.setPosition({ position.left, 768.f + position.top + position.height });
					rect.setRandomDarkColor();

				}
				break;
			case Direction::Left:
				if (position.left > 1366.f){
					rect.setPosition({ position.left - 1366.f - position.width, position.top });
					rect.setRandomDarkColor();
					
				}
				break;
			case Direction::Right:
				if (position.left + position.width < 0.f){
					rect.setPosition({ position.left + position.width + 1366.f, position.top });
					rect.setRandomDarkColor();

				}
				break;
			}
			
	}
}
void MenuBackground::draw(sf::RenderWindow& win){
	for (auto& rect : rectangles){
		rect.draw(win);
	}
}

MenuBackground::~MenuBackground(){
}
