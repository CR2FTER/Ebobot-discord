#pragma once
#include "Log.hpp"
#include <cstring>
#include <filesystem>
class LogConsole : public Log
{
public:
	void Logging(const std::string& message, ClassError error) noexcept override;
};
