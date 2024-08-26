#pragma once

enum class ClassError
{
	INFO, WARNING, ERROR, CRITICAL
};
class Log
{
public:
	virtual void logging(const std::string, ClassError) = 0;	
};
