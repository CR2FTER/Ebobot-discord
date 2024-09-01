#include "LogStream.hpp"
#include "TimeSet.hpp"
#include <type_traits>
#include <exception>
#include <iostream>
#include <mutex>
#include <iomanip>
void LogStream::Logging(const std::string& message, ClassError classError) noexcept
{
	char buffer[64];
	this->GetStringClassError(buffer, 64, classError);
	std::chrono::system_clock::time_point tP = std::chrono::system_clock::now();

	std::time_t timeSec = std::chrono::system_clock::to_time_t(tP);
	
	std::chrono::duration<std::uint64_t, std::nano> dur = tP.time_since_epoch();
	std::uint64_t nanoSec = (dur.count())%(std::nano::den);


	
	try{
		std::lock_guard l1(mutex_);
		std::tm gTM = *std::gmtime(&timeSec);
		errorStream_.fill('0');
		errorStream_ << '{' << std::put_time(&gTM, "%F %T") << '.' << std::setw(9) << nanoSec << "} "
		             << "[" << buffer << "]: \'"   
	  		     << message << '\'' << std::endl;

	}
	catch(const std::ios_base::failure& e)
	{
		std::cerr << e.what();
		std::error_code system_code;
		system_code.assign(e.code().value(), std::system_category());
		std::quick_exit(system_code.value());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
		std::quick_exit(-1);
	}
}

LogStream::LogStream(std::streambuf* stream): errorStream_(stream)
{
	errorStream_.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}
