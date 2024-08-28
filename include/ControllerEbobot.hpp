#pragma once
#include <string>
#include "Controller.hpp"
#include "User.hpp"
#include "Group.hpp"
#include "Command.hpp"

class ControllerEbobot : public Controller
{
public:
	std::string Handle(const User&, const Group&, const Command&) override;
};
