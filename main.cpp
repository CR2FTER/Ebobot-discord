#include <iostream>
#include "BotStarter.hpp"
#include "DiscordBotStarter.hpp"
#include "Storage.hpp"
int main()
{
	    DiscordBotStarter dsbot;
		
	    BotStarter& bot = dsbot;

	    bot.Start();
}
