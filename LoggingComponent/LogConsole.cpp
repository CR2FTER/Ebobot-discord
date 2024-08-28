#include "LogConsole.hpp"
#include <iostream>

void LogConsole::Logging(const std::string& message, ClassError classError) noexcept
{
	char buffer[64];
	this->GetStringClassError(buffer, 64, classError);
	std::cout << buffer << ' ' << message << std::endl;
}
