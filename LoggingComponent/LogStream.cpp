#include "LogStream.hpp"
#include <type_traits>
#include <exception>
#include <iostream>
#include <mutex>
#include <cstring>

bool LogStream::createRecord_
     (char* record, std::size_t count, const std::tm* tp,
     std::uint32_t nano, const char* message
     , std::size_t sizeMessage, ClassError classError) const noexcept
{

	{
		std::size_t i = 0;
		for(; (*(message+i) != 0) && i < (sizeMessage ); i++)
		{}
		
		sizeMessage = i;
	}

	count -= 18;
	
	
	
	std::size_t sizeTime = 0;
	*(record+(sizeTime++)) = '{';
	if(tp != nullptr){ //if have value 
		std::size_t t = strftime(record+sizeTime, count, "%F %T.", tp);
		if(t != 0)
		{
			sizeTime += t;
			count -= t;
		}
		else
			return false;
	}
	if (sizeTime == 1) //if it not changed (strftime return 0 or don`t have value)
	{
		std::memcpy(record+sizeTime, "TimeERROR",  9);
	}
	else{
		for(std::uint8_t i = 9; i >= 1; i--) //.000000000}
		{
			std::uint8_t num = nano%10;
			*(record+sizeTime+i-1) = num + 0x30;
			nano/=10;
		}
	}
	
	sizeTime+=9;
	*(record+(sizeTime++)) = '}';	
	*(record+(sizeTime++)) = ' ';	
	*(record+(sizeTime++)) = '[';	

	std::size_t classSize = GetStringClassError(record+sizeTime, count+1, classError);
	if(classSize == 0)
		return false;

	sizeTime += classSize - 1;
	count -= classSize - 1;
	*(record+(sizeTime++)) = ']';
	*(record+(sizeTime++)) = ':';	
	*(record+(sizeTime++)) = ' ';
	
	std::size_t sizeCopy = (sizeMessage < count)? (sizeMessage): (count);

	std::memcpy(record+sizeTime, message,
			 	sizeCopy	
			 	);
	sizeTime+= sizeCopy;
	*(record+(sizeTime++)) = '\n';
	*(record+(sizeTime++)) = 0;
	return true;

}


bool LogStream::Logging(const char* message, std::size_t count, ClassError classError) noexcept
{
	if(message == nullptr)
		return false;
	std::tm gTM;
	std::tm* gTMptr = nullptr;
	
	std::uint64_t nanoSec = 0;
	
	std::chrono::system_clock::time_point tP = std::chrono::system_clock::now();
	std::time_t timeSec = std::chrono::system_clock::to_time_t(tP);
	
	char arr[8192]; //buffer for a log record
		
		
	try{
		std::chrono::duration<std::uint64_t, std::nano> dur = tP.time_since_epoch(); //can throw exception
		nanoSec = (dur.count())%(std::nano::den);
		{
			std::lock_guard l(gmtimeLock_);
			std::tm* pTm = std::gmtime(&timeSec); //can return null
			if(pTm != nullptr)
			{
				gTM = *pTm;
				gTMptr = &gTM; //If ok, Set value
			}
		}
	}
	catch(...) //if throw, set null
	{
		gTMptr = nullptr;
	}
		
	try{
		if(!createRecord_(arr, sizeof(arr), gTMptr, nanoSec, message,  count, classError))
			return false;

		{
			std::lock_guard l(mutex_);
			errorStream_ << arr; //can throw exception 
			errorStream_.flush();
		}

	}
	catch(const std::ios_base::failure& e)
	{
		std::lock_guard l(mutex_);
		std::cerr.exceptions(std::ios_base::goodbit);
		std::cerr.clear();
		errorStream_.flush();
		std::cerr << arr << ' ' << e.what() << std::endl;
		std::error_code system_code;
		system_code.assign(e.code().value(), std::system_category());
		std::quick_exit(system_code.value());
	}
	catch(const std::exception& e)
	{
		std::lock_guard l(mutex_);
		std::cerr.exceptions(std::ios_base::goodbit);
		std::cerr.clear();
		errorStream_.flush();
		std::cerr << arr << ' ' << e.what() << std::endl;
		std::quick_exit(-1);
	}
	catch(...)
	{
		std::lock_guard l(mutex_);
		std::cerr.exceptions(std::ios_base::goodbit);
                std::cerr.clear();
		std::cerr << "Critical Error of Logger" << std::endl;
		std::quick_exit(-1);
	}
	return true;
}

LogStream::LogStream(std::ofstream&& stream): errorStream_(std::move(stream))
{
	errorStream_.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

