#pragma once
#include "BotStarter.hpp"
class DiscordBotStarter : public BotStarter
{
	void Start() override;
	void SetController(const Controller&) override;
};
