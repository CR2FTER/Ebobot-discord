#include <dpp/dpp.h>
#include "DiscordBotStarter.hpp"
#include <iostream>
#include <cstddef>

DiscordBotStarter::DiscordBotStarter(const std::string& str,
		const std::shared_ptr<Log>& logger) : token_(str), logger_(logger)
{} 

void DiscordBotStarter::Start(Controller& controller)
{
	dpp::cluster bot(token_, dpp::i_default_intents | dpp::i_message_content);
	bot.on_log([this](const dpp::log_t& event)
	{
		dpp::loglevel dsClassError = event.severity;
		ClassError classError;
		if(dsClassError == dpp::loglevel::ll_warning)
			classError = ClassError::WARNING;
		else if(dsClassError == dpp::loglevel::ll_error)
			classError = ClassError::ERROR;
		else if(dsClassError == dpp::loglevel::ll_critical)
			classError = ClassError::CRITICAL;
		else 
			classError = ClassError::INFO;
			
		logger_->Logging(event.message.c_str(), event.message.size(), classError);		
	});

	bot.on_slashcommand([&controller](const dpp::slashcommand_t & event) {
		const dpp::user& dsUser = event.command.usr;	
		User user{dsUser.username, dsUser.id.str()};
		Group group{event.command.get_guild().id.str()};
		Command command{event.command.get_command_name()};
		event.reply(controller.Handle(user, group, command));
	});	
	bot.start(dpp::st_wait);
}


