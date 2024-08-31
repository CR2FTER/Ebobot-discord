#include <iostream>
#include "BotStarter.hpp"
#include "DiscordBotStarter.hpp"
#include "Storage.hpp"
#include "LogConsole.hpp" 
#include "ControllerEbobot.hpp"
#include <memory>
#include "FakeStorage.hpp"

int main()
{
	std::shared_ptr<FakeStorage> storage;
	std::shared_ptr<LogConsole> log;
	DiscordBotStarter dsbot("", log);	
	ControllerEbobot controller(storage, log);	
	BotStarter& bot = dsbot;
	bot.Start(controller);
}

