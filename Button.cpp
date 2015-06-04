#include "Button.h"
#include "Game.h"
//class Button :
//	public MovingObject
//{
//public:
//		Button(const std::string str, const Scene::ExitAction _action, const SVector2f& startPosition
//				, const SVector2f& speed, const SVector2f& end);
//	void draw(sf::RenderWindow& window) override;
//	const bool exists() override{
//		return true;
//	}
//	void move(sf::Int32 time) override;
//	Scene::ExitAction isPressed();
//	~Button();
//private:
//	Scene::ExitAction action;
//	sf::Text text;
//	sf::RectangleShape background;
//};



Button::Button(const std::string _text, const Scene::ExitAction _action, const SVector2f& startPosition
															, const SVector2f& _speed, const SVector2f& end, float expandCoff )
	: action(_action)
	, text(_text, Game::getFont(), static_cast<unsigned>(50.f * SVector2f::getConversation().y))
	, background(SVector2f(300.f * expandCoff, 78.f))
	, speed(_speed) , finishedMovement(false)
	, endPosition(end){
	background.setPosition(startPosition);
	text.setPosition(SVector2f{ startPosition.x + background.getGlobalBounds().width / 2.f - text.getGlobalBounds().width / 2.f
		, startPosition.y + background.getGlobalBounds().height / 2.f - text.getCharacterSize() / 2.f });
	text.setColor(sf::Color::White);
	background.setFillColor(sf::Color(150,150,150,125));
	
}
void Button::draw(sf::RenderWindow& window){
	window.draw(background);
	window.draw(text);
}
void Button::move(const sf::Int32 time) {
	if (finishedMovement)
		return;
	const SVector2f position = background.getPosition();
	if ((speed.x > FLT_EPSILON && position.x < endPosition.x)
		|| (speed.x < -FLT_EPSILON && position.x > endPosition.x)
		|| (speed.y > FLT_EPSILON && position.y < endPosition.y)
		|| (speed.y < -FLT_EPSILON && position.y > endPosition.y)){
			const SVector2f move{speed.x * static_cast<float>(time), speed.y * static_cast<float>(time)};
			text.move(speed.x * time, speed.y * time);
			background.move(speed.x * time, speed.y * time);
	}
	else{
		background.setPosition(endPosition);
		text.setPosition(SVector2f{ endPosition.x + background.getGlobalBounds().width / 2.f - text.getGlobalBounds().width / 2.f
			, endPosition.y + background.getGlobalBounds().height / 2.f - text.getCharacterSize() / 2.f });
		finishedMovement = true;
	}
}
const Scene::ExitAction Button::press(){
	return action;
}
void Button::select(){
	background.setFillColor(sf::Color(50, 50, 50, 180));
}
void Button::unselect(){
	background.setFillColor(sf::Color(150, 150, 150, 125));
}
void Button::setText(const std::string& _text){
	text.setString(_text);
}
Button::~Button(){
}
