#include "Biplane.h"
#include "SRect.h"
#include "SVector2.h"
#include <math.h>
#define SPEED_COFF .2f
#define ACC_COFF .0025f

Biplane::Biplane(const sf::Texture* _texture, const Biplane::StartPosition _position) : biplane(*_texture)
					, isInAir(false), position(_position)
					, health(_position), CollidingObject(CollidingObject::Weight::Biplane){
	const SFloatRect rect = biplane.getGlobalBounds();
	SVector2f factor;
	if (_position == Biplane::StartPosition::Left){
		currentAngle = 0.f;
		factor = SVector2f{ 100.f / rect.width, 35.f / rect.height };
	}
	else{
		currentAngle = 180.f;
		factor = SVector2f{ 100.f / -rect.width, 35.f / rect.height };
	}
	
	biplane.setScale(factor);
	
	if (position == StartPosition::Left){
		biplane.setPosition(SVector2f(0.f, 668.f - 34.f));
	}
	else{
		biplane.setPosition(SVector2f(1366.f, 668.f - 40.f));
	}
	biplane.setOrigin(biplane.getGlobalBounds().width / 2, biplane.getGlobalBounds().height / 2);
}
void Biplane::die(){
	health.hp = -1.f;
}
const bool Biplane::flies(){
	return isInAir;
}
const SVector2f& Biplane::getSpeed(){
	return speed;
}
std::shared_ptr<Bullet> Biplane::fireBullet(){
	if (!isInAir){
		return nullptr;
	}
	if (bulletFireTimer.getElapsedTime().asMilliseconds() > 300){
		bulletFireTimer.restart();
		const SFloatRect bounds = getBounds();
		return std::shared_ptr<Bullet>(new Bullet(
			{ bounds.left + bounds.width / 2 + 80.f * speed.x, bounds.top + bounds.height / 2 + 80.f * speed.y }
			, { speed.x * 2 * SPEED_COFF, speed.y * 2 * SPEED_COFF }));
	}
	else
		return nullptr;
}
const bool Biplane::exists(){
	return health.exists();
}
void Biplane::draw(sf::RenderWindow& window){
	health.draw(window);
	window.draw(biplane);
}
void Biplane::move(const sf::Int32 time){
	const SVector2f move(speed.x * static_cast<float>(time) * SPEED_COFF, speed.y * static_cast<float>(time) * SPEED_COFF);
	biplane.move(move);
	if (getBounds().intersects(SFloatRect{-103.f, 0.f, 1.f, 768.f })){
		biplane.move(SVector2f{1469.f,0.f});
	}
	else if (getBounds().intersects(SFloatRect{ 1472.f, 0.f, 1.f, 768.f })){
		biplane.move(SVector2f{-1469.f, 0.f});
	}
}
void Biplane::collide(CollidingObject::Weight w){
	switch (w){
	case CollidingObject::Weight::Biplane:
		health.hp -= 0.1f;
		break;
	case CollidingObject::Weight::Ground:
		health.hp -= 6.f;
		break;
	case CollidingObject::Weight::Sky:
		health.hp -= 3.f;
		break;
	case CollidingObject::Weight::Bullet:
		health.hp -= 10.f;
		break;
	}
}
const sf::FloatRect Biplane::getBounds(){
	return biplane.getGlobalBounds();
}
void Biplane::changeSpeed(const Direction dir, const sf::Int32 time){
	if (!isInAir){
		if (position == StartPosition::Left && dir == Right){
			speed.x += ACC_COFF * time/6;
		}
		else if (position == StartPosition::Right && dir == Left){
			speed.x -= ACC_COFF * time/6;
		}
		if (fabs(speed.x) >= 1.f){
			isInAir = true;
		}
	}
	else{
		switch (dir){
		case Left:	speed.x -= ACC_COFF * time; break;
		case Right: speed.x += ACC_COFF * time; break;
		case Up: speed.y -= ACC_COFF * time; break;
		case Down: speed.y += ACC_COFF * time; break;
		}
		speed.normalize();
		currentAngle = (180.f / 3.14f) * atan(fabs(speed.y / speed.x));
		if (speed.x < 0.f && speed.y < 0.f){
			currentAngle += 180;
		}
		else if (speed.y < 0.f){
			currentAngle *= -1;
		}
		else if (speed.x < 0.f){
			currentAngle = 180 - currentAngle;
		}
		if (position == Biplane::StartPosition::Right){
			currentAngle += 180;
		}
		
		biplane.setRotation(currentAngle);
	}
}
Biplane::~Biplane()
{
}
