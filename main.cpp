#include <iostream>
#include "BotStarter.hpp"
#include "DiscordBotStarter.hpp"
#include "Storage.hpp"
#include "LogConsole.hpp" 
#include "ControllerEbobot.hpp"
int main()
{
	DiscordBotStarter dsbot;
	ControllerEbobot controller;	
	BotStarter& bot = dsbot;
	bot.Start(controller);
}
