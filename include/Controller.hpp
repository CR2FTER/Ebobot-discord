#pragma once
#include <string>
#include "User.hpp"
#include "Group.hpp"
#include "Command.hpp"

class Controller
{
	virtual std::string Handle(const User&, const Group&, const Command&) = 0;
};
