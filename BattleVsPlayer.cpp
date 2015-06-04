#include "BattleVsPlayer.h"


BattleVsPlayer::BattleVsPlayer(sf::RenderWindow& window) : Battle(window, Battle::Mode::VsPlayer)
{
}

void BattleVsPlayer::rightPlayerTurn(const sf::Int32 time){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		rightPlane->changeSpeed(Up, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		rightPlane->changeSpeed(Down, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		rightPlane->changeSpeed(Left, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		rightPlane->changeSpeed(Right, time);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)){
		auto bullet = rightPlane->fireBullet();
		if (bullet){
			manager.add(bullet);
			collider.add(bullet);
		}
	}
}
BattleVsPlayer::~BattleVsPlayer()
{
}
