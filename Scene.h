#pragma once
#include "Header.h"
#include "MoveManager.h"
class Scene
{
public:
	Scene(sf::RenderWindow& win) : window(win), manager(win){

	}
	enum class ExitAction{ RunMainMenu, RunOptions, RunPlayModeSelect, Exit, Error, NoAction
		, RunGameVsAI, RunGameVsPlayer, GoBack, RunAbout, ChangeDifficutlty, ChangeResolution
		, ChangeScreenMode, Save};
	virtual const ExitAction run(){
		return ExitAction::Error;
	}
	virtual ~Scene(){}
protected:
	virtual void render() = 0;
	virtual const ExitAction processEvents() = 0;
	sf::RenderWindow& window;
	MoveManager manager;

};

