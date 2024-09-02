#pragma once
#include "Log.hpp"
#include <string>
#include <ostream>
#include "SpinLock.hpp"
#include <ctime>

class LogStream : public Log
{
public:
	LogStream(std::streambuf*);
	bool Logging(const char* message, std::size_t count, ClassError error) noexcept override;
private:
	bool createRecord_(char*, std::size_t, const std::tm*,
		        std::uint32_t, const char*, std::size_t, ClassError) const noexcept;

	std::ostream errorStream_;
	SpinLock mutex_;
	SpinLock gmtimeLock_;
};
