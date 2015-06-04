#include "Log.h"

std::ofstream Log::log;

void Log::open(){
	log.open("game.log", std::ios::out);
	if (!log){
		throw GameException("Error openning Log", "Log::open()", false);
	}
}
void Log::close(){
	if (log.is_open())
		log.close();
}
void Log::write(std::string message){
	if (!log)
		throw GameException("Error writting message: \"" + message + "\"", "Log::write()", false);
	else
		log << message << std::endl;
}

