#include <iostream>
#include "BotStarter.hpp"
#include "DiscordBotStarter.hpp"
#include "Storage.hpp"
#include "LogConsole.hpp" 
#include "ControllerEbobot.hpp"
#include <memory>
int main()
{
	std::shared_ptr<LogConsole> log;
	DiscordBotStarter dsbot("", log);
	
	ControllerEbobot controller;	
	BotStarter& bot = dsbot;
	bot.Start(controller);
}
