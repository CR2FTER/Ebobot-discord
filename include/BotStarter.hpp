#pragma once

#include "Controller.hpp"
class BotStarter
{
public:
	virtual void Start() = 0;
	virtual void SetController(const Controller&) = 0;
};
