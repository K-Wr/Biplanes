#pragma once
#include "Battle.h"
#include "Settings.h"
class BattleVsAI :
	public Battle
{
public:
	BattleVsAI(sf::RenderWindow& window, const Settings::Difficulty difficulty);
	~BattleVsAI();
protected:
	const SVector2f& speed;
	int difficulty;
	void rightPlayerTurn(const sf::Int32 time) override;
};

