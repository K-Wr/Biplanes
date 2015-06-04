#include "GameException.h"


GameException::GameException(std::string _text, std::string _source, bool writeToLog) : text(_text)
																							, source(_source){
	if (writeToLog){
		Log::write("\nEXCEPTION THROWN:\n" + _text + " occured at " + source);
	}
}


GameException::~GameException()
{
}
