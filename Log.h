#pragma once
#include "Header.h"
class Log
{
public:
	static void open();
	static void close();
	static void write(const std::string message);
private:
	static std::ofstream log;
};

