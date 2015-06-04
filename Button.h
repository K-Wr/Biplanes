#pragma once
#include "MovingObject.h"
#include "Scene.h"
#include "SVector2.h"
#include <string>
class Button :
	public MovingObject
{
public:
	Button(const std::string _text, const Scene::ExitAction _action
		, const SVector2f& startPosition, const SVector2f& speed, const SVector2f& end
		, float expandCoff = 1.f);
	void draw(sf::RenderWindow& window) override;
	const bool exists() override{
		return true;
	}
	void move(const sf::Int32 time) override;
	void setText(const std::string& text);
	void select();
	void unselect();
	const Scene::ExitAction press();
	~Button();
private:
	bool finishedMovement;
	SVector2f endPosition;
	sf::Vector2f speed;
	Scene::ExitAction action;
	sf::Text text;
	sf::RectangleShape background;
};

