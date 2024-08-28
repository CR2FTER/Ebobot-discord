#include "Log.hpp"
#include <cstring>
bool Log::GetStringClassError(char* buffer, std::size_t max, ClassError error) const noexcept
{
	if(max < 9)
		return false;
	switch(error)
	{
	case ClassError::INFO:
		std::memcpy(buffer, "INFO", 5);
		break;
	case ClassError::WARNING:
		std::memcpy(buffer, "WARNING", 8);
		break;
	case ClassError::ERROR:
		std::memcpy(buffer, "ERROR", 6);
		break;
	case ClassError::CRITICAL:
		std::memcpy(buffer, "CRITICAL", 9);
		break;
	}
	return true;
}
