#pragma once
#include "Controller.hpp"
#include "Log.hpp"

class BotStarter
{
public:
	virtual void Start(Controller&) = 0;
};
