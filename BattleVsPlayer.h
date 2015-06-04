#pragma once
#include "Battle.h"
class BattleVsPlayer :
	public Battle
{
public:
	BattleVsPlayer(sf::RenderWindow& window);
	~BattleVsPlayer();
protected:
	void rightPlayerTurn(const sf::Int32 time) override;
};

