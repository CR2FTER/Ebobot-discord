#include "Log.hpp"
#include <cstring>
std::size_t Log::GetStringClassError(char* buffer, std::size_t max, ClassError error) const noexcept
{
	if(max < 9)
		return 0;

	std::size_t sizeT;
	switch(error)
	{
	case ClassError::INFO:
		std::memcpy(buffer, "INFO", 5);
		sizeT = 5;
		break;
	case ClassError::WARNING:
		std::memcpy(buffer, "WARNING", 8);
		sizeT = 8;
		break;
	case ClassError::ERROR:
		std::memcpy(buffer, "ERROR", 6);
		sizeT = 6;
		break;
	case ClassError::CRITICAL:
		std::memcpy(buffer, "CRITICAL", 9);
		sizeT = 9;
		break;
	}
	return sizeT;
}
