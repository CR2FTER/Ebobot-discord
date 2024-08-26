#include <dpp/dpp.h>
#include "DiscordBotStarter.hpp"
#include <iostream>


void DiscordBotStarter::Start()
{
	dpp::cluster bot("token", dpp::i_default_intents | dpp::i_message_content);
	bot.on_log(dpp::utility::cout_logger());
	bot.on_message_create([&bot](const dpp::message_create_t& event) {
		if (event.msg.content.find("bad word") != std::string::npos) {
			event.reply("That is not allowed here. Please, mind your language!", true);
		}
	});
	bot.start(dpp::st_wait);
}


void DiscordBotStarter::SetController(const Controller& )
{}
