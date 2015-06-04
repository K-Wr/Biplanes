#include "BattleVsAI.h"

BattleVsAI::BattleVsAI(sf::RenderWindow& window, const Settings::Difficulty _difficulty) 
					: Battle(window, Battle::Mode::VsAI)
					, difficulty((int)_difficulty), speed(rightPlane->getSpeed())
{
}

void BattleVsAI::rightPlayerTurn(const sf::Int32 time){
	
	if (!rightPlane->flies()){
		rightPlane->changeSpeed(Left, time);
	}
	else{
		const SFloatRect enemyBounds = leftPlane->getBounds();
		const SVector2f enemy{ enemyBounds.left + enemyBounds.width / 2, enemyBounds.top + enemyBounds.height / 2 };
		const SFloatRect planeBounds = rightPlane->getBounds();
		const SVector2f plane{ planeBounds.left + planeBounds.width / 2, planeBounds.top + planeBounds.height / 2 };
		auto bullet = rightPlane->fireBullet();
		if (bullet){
			manager.add(bullet);
			collider.add(bullet);
		}
		if (difficulty != 3){
			if (plane.y > 640.f - (4 - difficulty) * 10.f){
				if (speed.x > 0.f && speed.x < 0.5f){
					rightPlane->changeSpeed(Right, time);
				}
				else if (speed.x < 0.f && speed.x > -0.5f){
					rightPlane->changeSpeed(Left, time);
				}
				rightPlane->changeSpeed(Up, time);
				return;
			}
			if (plane.y < 0.f + (4 - difficulty) * 15.f){
				if (speed.x > 0.f && speed.x < 0.5f){
					rightPlane->changeSpeed(Right, time);
				}
				else if (speed.x < 0.f && speed.x > -0.5f){
					rightPlane->changeSpeed(Left, time);
				}
				rightPlane->changeSpeed(Down, time);
				return;
			}
		}
		if (enemy.x + 40.f + 70.f*difficulty < plane.x){
			rightPlane->changeSpeed(Left, time);
		}
		else if (enemy.x - 40.f - 70.f * difficulty > plane.x){
			rightPlane->changeSpeed(Right, time);
		}
		if (enemy.y - 20.f - 35.f * difficulty > plane.y){
			rightPlane->changeSpeed(Down, time);
		}
		else if (enemy.y + 20.f + 35.f * difficulty < plane.y){
			rightPlane->changeSpeed(Up, time);
		}
		
	}
}
BattleVsAI::~BattleVsAI()
{
}
