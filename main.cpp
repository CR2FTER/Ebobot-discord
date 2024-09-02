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


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::shared_ptr<Log> log(new LogStream(std::cerr.rdbuf()));
	std::shared_ptr<Storage> storage(new FakeStorage(logger));
	DiscordBotStarter dsbot("", log);	
	ControllerEbobot controller(storage, log);	
	BotStarter& bot = dsbot;
	bot.Start(controller);

}

