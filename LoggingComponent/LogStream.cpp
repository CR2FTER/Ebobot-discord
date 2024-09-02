#include "LogStream.hpp"
#include "TimeSet.hpp"
#include <type_traits>
#include <exception>
#include <iostream>
#include <mutex>
#include <iomanip>
#include <cstring>
bool LogStream::createRecord_
     (char* record, std::size_t count, const std::tm* tp,
     std::uint32_t nano, const char* message
     , std::size_t sizeMessage, ClassError classError) const noexcept
{
	if(count < 17 + sizeMessage)
		return false;

	count-=17 + sizeMessage;

	std::size_t sizeTime = strftime(record, count, "{%F %T.", tp);
	if(sizeTime == 0)
		return false;

	count -= sizeTime - 1;

	for(std::uint8_t i = 9; i >= 1; i--)
	{
		std::uint8_t num = nano%10;
		*(record+sizeTime+i-1) = num + 0x30;
		nano/=10;
	}
	sizeTime += 9;
	*(record+(sizeTime++)) = '}';	
	*(record+(sizeTime++)) = ' ';	
	*(record+(sizeTime++)) = '[';	

	std::size_t classSize = GetStringClassError(record+sizeTime, count+1, classError);
	if(classSize == 0)
		return false;

	sizeTime += classSize -1;

	*(record+(sizeTime++)) = ']';
	*(record+(sizeTime++)) = ':';	
	*(record+(sizeTime++)) = ' ';
	std::memcpy(record+sizeTime, message, sizeMessage);
	sizeTime+= sizeMessage;
	*(record+(sizeTime++)) = '\n';
	*(record+(sizeTime++)) = 0;
	return true;

}


bool LogStream::Logging(const char* message, std::size_t count, ClassError classError) noexcept
{
	std::chrono::system_clock::time_point tP = std::chrono::system_clock::now();
	std::time_t timeSec = std::chrono::system_clock::to_time_t(tP);
	std::chrono::duration<std::uint64_t, std::nano> dur = tP.time_since_epoch();
	std::uint64_t nanoSec = (dur.count())%(std::nano::den);
	
	try{
		char arr[65000];
		std::tm gTM;
		{
			std::lock_guard l(gmtimeLock_);
			gTM = *std::gmtime(&timeSec);
		}
		if(!createRecord_(arr, sizeof(arr), &gTM, nanoSec, message,  count, classError))
			return false;

		{
			std::lock_guard l(mutex_);
			errorStream_ << arr;
			errorStream_.flush();
		}


		return true;
	}
	catch(const std::ios_base::failure& e)
	{
		errorStream_.flush();
		std::cerr << e.what() << std::endl;
		std::error_code system_code;
		system_code.assign(e.code().value(), std::system_category());
		std::quick_exit(system_code.value());
	}
	catch(const std::exception& e)
	{
		errorStream_.flush();
		std::cerr << e.what() << std::endl;
		std::quick_exit(-1);
	}
}

LogStream::LogStream(std::streambuf* stream): errorStream_(stream)
{
	Logging("Logger Created!", 15, ClassError::INFO);
	errorStream_.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

