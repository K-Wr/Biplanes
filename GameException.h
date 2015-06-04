#pragma once
#include "Header.h"
class GameException
{
public:
	GameException(const std::string _text, const std::string _source, const bool writeToLog = true);
	~GameException();
	const std::string text;
	const std::string source;
};

