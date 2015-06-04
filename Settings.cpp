#include "Settings.h"


Settings::Settings()
{
	
	std::ifstream settingsFile("settings", std::ios::binary);
	if (!settingsFile){
		loadDefaults();
		Log::write("Default settings loaded successfully");
		save();
	}
	else{
		unsigned char tempDiff, tempMode;
		settingsFile >> tempDiff;
		difficulty = static_cast<Difficulty>(tempDiff);
		settingsFile >> tempMode;
		screenMode = static_cast<ScreenMode>(tempMode);
		settingsFile >> windowSize.x;
		settingsFile >> windowSize.y;
		settingsFile.close();
		const sf::Vector2u currentResolution = {
			sf::VideoMode::getDesktopMode().width
			, sf::VideoMode::getDesktopMode().height };
		if (windowSize.x + FLT_EPSILON > currentResolution.x 
			|| windowSize.y + FLT_EPSILON > currentResolution.y
			|| tempDiff > 3 || tempMode > 1){
			Log::write("\nERROR loading settings:"
				"Settings doesn\'t match, loading defaults; error skipped \n");
			loadDefaults();
			save();
		}
		else
			Log::write("Settings load successfully");
	}
	settingsFile.close();
}


void Settings::loadDefaults(){
	difficulty = Difficulty::medium;
	screenMode = ScreenMode::windowed;
	windowSize = sf::Vector2u(800U, 600U);
}
Settings::Settings(const Difficulty _difficulty, const ScreenMode _mode, const sf::Vector2u& _wsize){
	difficulty = _difficulty;
	screenMode = _mode;
	windowSize = _wsize;
	
}
void Settings::set(const Settings& set){
	difficulty = set.difficulty;
	screenMode = set.screenMode;
	windowSize = set.windowSize;
	save();

}
void Settings::save(){
	std::ofstream settingsFile("settings", std::ios::binary);
	if (!settingsFile){
		throw GameException("Error openning settings file", "Settings::save()");
	}

	settingsFile << static_cast<unsigned char>(difficulty);
	settingsFile << static_cast<unsigned char>(screenMode);
	settingsFile << " ";
	settingsFile << windowSize.x;
	settingsFile << " ";
	settingsFile << windowSize.y;
	settingsFile.close();
	Log::write("Settings saved to file successfully");
	settingsFile.close();
}
Settings::~Settings()
{
}
