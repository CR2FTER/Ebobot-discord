#pragma once
#include <string>
#include <memory>
#include "Controller.hpp"
#include "User.hpp"
#include "Group.hpp"
#include "Command.hpp"
#include "Storage.hpp"
#include "Log.hpp"

class ControllerEbobot : public Controller
{
public:
	ControllerEbobot(const std::shared_ptr<Storage>&, const std::shared_ptr<Log>&);
	std::optional<std::string> Handle(const User&, const Group&, const Command&) override;
private:
	std::shared_ptr<Storage> storage_;
	std::shared_ptr<Log> log_;
};
