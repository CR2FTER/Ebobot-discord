#pragma once
#include <string>
#include <optional>
#include "User.hpp"
#include "Group.hpp"
#include "Command.hpp"

class Controller
{
public:
	virtual std::optional<std::string> Handle(const User&, const Group&, const Command&) = 0;
};
