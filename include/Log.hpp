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
	virtual void Logging(const std::string&, ClassError) noexcept = 0;	
protected:
	bool GetStringClassError(char*,std::size_t, ClassError) const noexcept;
};
