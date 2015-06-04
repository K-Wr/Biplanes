#pragma once
#include "MovingObject.h"
#include "CollidingObject.h"
#include "SVector2.h"
#include "TextureManager.h"
#include "SRect.h"
class Bullet :
	public MovingObject, public CollidingObject{
public:
	enum class Type{Default};
	Bullet(const SVector2f& startPosition, const SVector2f& _speed, Type type = Type::Default) 
		: CollidingObject(CollidingObject::Weight::Bullet)
		, speed(_speed){
		if (type == Type::Default){
			sprite.setTexture(*TextureManager::getTexture(TextureManager::TextureName::DefaultBullet));
		}
		sprite.setPosition(startPosition);
		SVector2f scale = { 3.f, 3.f };
		if (((sf::Vector2f)scale).x > 1.f && ((sf::Vector2f)scale).y > 1.f)
			sprite.setScale(scale);
		else
			sprite.setScale({ 1.f, 1.f });
	}
	void draw(sf::RenderWindow& window) override{
		window.draw(sprite);
	}
	void move(const sf::Int32 time) override{
		sprite.move(speed.x * time, speed.y * time);
		SFloatRect coords = getBounds();
		if (coords.left < -120.f || coords.left > 1600.f || coords.top < -100.f){
			existance = false;
		}
	}
	void die(){
		existance = false;
	}
	const sf::FloatRect getBounds() override{
		return sprite.getGlobalBounds();
	}
	void collide(const CollidingObject::Weight weight) override{
		existance = false;
	}
	const bool exists() override{
		return existance;
	}
	~Bullet(){}
private:
	sf::Vector2f speed;
	sf::Sprite sprite;
	bool existance;
};

