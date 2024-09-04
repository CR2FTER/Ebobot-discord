#include <iostream>
#include "BotStarter.hpp"
#include "DiscordBotStarter.hpp"
#include "Storage.hpp"
#include "LogStream.hpp" 
#include "ControllerEbobot.hpp"
#include <memory>
#include "FakeStorage.hpp"
#include <thread>
#include "SpinLock.hpp"
#include <cstring>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::shared_ptr<Log> log(new LogStream(std::ofstream("log.txt", std::ios_base::app | std::ios_base::out)));
	try{
		std::shared_ptr<Storage> storage(new FakeStorage(log));
		DiscordBotStarter dsbot("", log);	
		ControllerEbobot controller(storage, log);	
		BotStarter& bot = dsbot;
		bot.Start(controller);
	}
	catch(std::exception& e)
	{
		const char* message = e.what();
		log->Logging(message, std::strlen(message), ClassError::CRITICAL);	
	}
	catch(...)
	{
		log->Logging("Unexpected internal error!!!", 28, ClassError::CRITICAL);
	}
}

