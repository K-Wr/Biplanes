#pragma once
#include "Scene.h"
#include "Biplane.h"
#include "CollisionManager.h"
class Battle : public Scene
{
protected:
	enum class Mode { VsPlayer, VsAI } mode;
public:

	Battle(sf::RenderWindow& window, const Mode _mode);
	const Scene::ExitAction run() override;
	~Battle();
protected:
	void render() override;
	const Scene::ExitAction processEvents() override;
	void leftPlayerTurn(const sf::Int32 time);
	virtual void rightPlayerTurn(const sf::Int32 time) = 0;
	std::shared_ptr<Biplane> leftPlane;
	std::shared_ptr<Biplane> rightPlane;
	CollisionManager collider;
private:
	void addRandomBackground();
	sf::Clock timer;
};

