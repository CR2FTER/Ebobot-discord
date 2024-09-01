#pragma once
#include "Log.hpp"
#include <string>
#include <ostream>
#include "SpinLock.hpp"
class LogStream : public Log
{
public:
	LogStream(std::streambuf*);
	void Logging(const std::string& message, ClassError error) noexcept override;
private:
	std::ostream errorStream_;
	SpinLock mutex_;
};
