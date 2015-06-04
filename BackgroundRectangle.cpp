#include "BackgroundRectangle.h"

void BackgroundRectangle::move(sf::Int32 time){
	const SVector2f move(speed.x * static_cast<float>(time), speed.y * static_cast<float>(time));
	shape.move(move);
}
BackgroundRectangle::BackgroundRectangle(SVector2f size, SVector2f start_position, SVector2f _svSpeed) : speed(_svSpeed),
																									shape(size){
	
	shape.setPosition(start_position);
	setRandomDarkColor();
}
void BackgroundRectangle::setPosition(const SVector2f& position){
	shape.setPosition(position); 
}
const SFloatRect BackgroundRectangle::getPosition(){
	return SFloatRect(shape.getGlobalBounds());
}
void BackgroundRectangle::draw(sf::RenderWindow& window){
	window.draw(shape);
}
BackgroundRectangle::~BackgroundRectangle(){
}
void BackgroundRectangle::setRandomDarkColor(){
	//srand(static_cast<unsigned>(time(nullptr)));
	const unsigned char R = rand() % 100 + 30;
	//srand(static_cast<unsigned>(time(nullptr)));
	const unsigned char G = rand() % 100 + 30;
	const unsigned char B = rand() % 100 + 30;
	shape.setFillColor(sf::Color(R,G,B));
}