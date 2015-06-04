#pragma once
#include "Header.h"
class Settings
{
public:
	enum class Difficulty{ death, hard, medium, easy };
	enum class ScreenMode{ fullscreen, windowed };
	Settings();
	Settings(const Difficulty _difficulty, const ScreenMode _mode, const sf::Vector2u& windowSize);
	void set(const Settings&);
	~Settings();
	
	void loadDefaults();

	Difficulty difficulty;
	ScreenMode screenMode;
	sf::Vector2u windowSize;
private:
	void save();
};

