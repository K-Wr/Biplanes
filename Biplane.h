#pragma once
#include "MovingObject.h"
#include "SVector2.h"
#include "CollidingObject.h"
#include "Bullet.h"
class Biplane : public MovingObject, public CollidingObject{
public:
	enum class StartPosition{Left, Right};
	Biplane(const sf::Texture* texture, const StartPosition);
	void draw(sf::RenderWindow& window) override;
	void move(const sf::Int32 time) override;
	void changeSpeed(const Direction dir, const sf::Int32 time);
	const bool exists() override;
	void collide(const CollidingObject::Weight w) override;
	const SVector2f& getSpeed();
	const sf::FloatRect getBounds() override;
	std::shared_ptr<Bullet> fireBullet();
	void die();
	const bool flies();
	~Biplane();
private:
	class Health {
	public:
		Health(const StartPosition position)
			: hpoints(100.f), background(SVector2f(350.f, 30.f)), foreground(SVector2f(350.f, 30.f)), existance(true) {
			if (position == StartPosition::Left){
				background.setPosition(SVector2f(100.f, 20.f));
				foreground.setPosition(SVector2f(100.f, 20.f));
			}
			else{
				background.setPosition(SVector2f(1366.f - 350.f - 100.f, 20.f));
				foreground.setPosition(SVector2f(1366.f - 350.f - 100.f, 20.f));
			}

			background.setFillColor({0,0,0});
			foreground.setFillColor({255,0,0});
		}
		void setHp(const float value){
			if (value > 0.f){
				hpoints = value;
				foreground.setSize(SVector2f(350.f * value / 100.f, 30.f));
			}
			else{
				existance = false;
				hpoints = 0.f;
			}
				
		}
		const float getHp(){
			return hpoints;
		}
		const bool exists(){
			return existance;
		}
		void draw(sf::RenderWindow& window){
			if (existance){
				window.draw(background);
				window.draw(foreground);
			}
		}
		__declspec (property(get = getHp, put = setHp)) float hp;
	private:
		bool existance;
		float hpoints;
		sf::RectangleShape background;
		sf::RectangleShape foreground;
	};
	sf::Clock bulletFireTimer;
	float currentAngle;
	Health health;
	StartPosition position;
	SVector2f speed;
	bool isInAir;
	sf::Sprite biplane;
};

