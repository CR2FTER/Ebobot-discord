#include <iostream>
#include "BotStarter.hpp"
#include "DiscordBotStarter.hpp"
#include "Storage.hpp"
#include "LogStream.hpp" 
#include "ControllerEbobot.hpp"
#include <memory>
#include "FakeStorage.hpp"




int main()
{
	std::shared_ptr<Log> log(new LogStream(std::cerr.rdbuf()));
	std::shared_ptr<Storage> storage(new FakeStorage(log));
	log->Logging("Test", ClassError::INFO);
	DiscordBotStarter dsbot("", log);	
	ControllerEbobot controller(storage, log);	
	BotStarter& bot = dsbot;
	bot.Start(controller);

}

