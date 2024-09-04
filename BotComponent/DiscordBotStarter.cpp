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

	bot.on_slashcommand([&controller, this](const dpp::slashcommand_t & event) {
		const dpp::user& dsUser = event.command.usr;	
		User user{std::move(dsUser.username), std::move(dsUser.id.str())};
		Group group{std::move(event.command.get_guild().id.str())};
		Command command{std::move(event.command.get_command_name())};
		try {
			std::optional<std::string> str = controller.Handle(user, group, command);
			if(str.has_value())
				event.reply(*str);
		}
		catch(std::bad_alloc& e)
		{
			logger_->Logging("BotStarter: Cannot allocate memory for reply", 41, ClassError::ERROR);
		}
		catch(std::exception& e)
		{
			const char* message = e.what();
			logger_->Logging(message, std::strlen(message), ClassError::ERROR);
		}
	});

	try
	{
		logger_->Logging("BotStarter: try to start a discord bot", 40, ClassError::INFO);
		bot.start(dpp::st_wait);
	}
	catch(dpp::exception& e)	
	{
		const char* message = e.what();
                logger_->Logging(message, std::strlen(message), ClassError::CRITICAL);
		logger_->Logging("Try to restart", 100 , ClassError::INFO);
		bot.start(dpp::st_wait);
	}

}


