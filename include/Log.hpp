#pragma once
#include <string>
#include <cstddef>

enum class ClassError
{
	INFO, WARNING, ERROR, CRITICAL
};
class Log
{
public:
	virtual bool Logging(const char*, std::size_t, ClassError) noexcept = 0;	
protected:
	std::size_t GetStringClassError(char*,std::size_t, ClassError) const noexcept;
};
