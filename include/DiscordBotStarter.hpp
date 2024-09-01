#pragma once
#include "BotStarter.hpp"
#include "Log.hpp"
#include <string>
#include <memory>

class DiscordBotStarter : public BotStarter
{
public:
	DiscordBotStarter(const std::string&, const std::shared_ptr<Log>& logger);
	void Start(Controller&) override;
private:
	std::string token_;
	std::shared_ptr<Log> logger_;
};
