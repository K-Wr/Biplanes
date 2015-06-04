#include "Game.h"
#include "Menu.h"
#include "PlayModeSelect.h"
#include "SVector2.h"
#include "Options.h"
#include "BattleVsAI.h"
#include "BattleVsPlayer.h"
#include "TextureManager.h"
#include "About.h"
sf::Font Game::font;
bool Game::fontLoaded = false;
Game::Game() : settings()
			,	window(sf::VideoMode(settings.windowSize.x, settings.windowSize.y)
						, "Biplanes v0.0"
						, (settings.screenMode == Settings::ScreenMode::fullscreen) ?
										sf::Style::Fullscreen : sf::Style::Default) {

	SVector2f::setConversation({1366.f, 768.f}
								, { static_cast<float>(settings.windowSize.x), static_cast<float>(settings.windowSize.y)});

	Log::write(std::string("Game constructed successfully with") + std::to_string(settings.windowSize.x) + "x" 
		+ std::to_string(settings.windowSize.y) + " as "  + 
		((settings.screenMode == Settings::ScreenMode::fullscreen)? "fullscreen" : "windowed")
		);
	window.setFramerateLimit(60);
	if (!font.loadFromFile("fonts\\font2.ttf")){
		throw GameException("Error loading font from file fonts\\font2.ttf ", "Game::Game()");
	}
	fontLoaded = true;
	srand(static_cast<unsigned>(time(nullptr)));
	window.setKeyRepeatEnabled(false);
	TextureManager::loadAllTextures();
	window.setMouseCursorVisible(false);
	
}
void Game::run(){
	Scene::ExitAction act = runScene(Scene::ExitAction::RunMainMenu);
	while (act != Scene::ExitAction::Exit){
		act = runScene(act);
	}
	window.close();
	Log::write("Window closed");
}

Scene::ExitAction Game::runScene(Scene::ExitAction act){
	switch (act){
	case Scene::ExitAction::RunMainMenu:
		Log::write("Runnig main menu");
		return Menu(window).run();
	case Scene::ExitAction::RunPlayModeSelect:
		Log::write("Running play mode select scene");
		return PlayModeSelect(window).run();
	case Scene::ExitAction::RunGameVsAI:
		Log::write("Running battle vs AI");
		return BattleVsAI(window, settings.difficulty).run();
	case Scene::ExitAction::RunGameVsPlayer:
		Log::write("Running battle vs Player");
		return BattleVsPlayer(window).run();
	case Scene::ExitAction::RunOptions:
		Log::write("Running options");
		return Options(window, settings).run();
	case Scene::ExitAction::RunAbout:
		Log::write("Running about");
		return About(window).run();
	default: throw GameException("No appropriate scene found", "Game::runScene()");
	}
}
const sf::Font& Game::getFont(){
	if (!fontLoaded){
		throw GameException("An attempt to use font, which is not loaded", "Game::getFont()");
	}
	return font;
}
Game::~Game(){
}
