#include "ControllerEbobot.hpp"

ControllerEbobot::ControllerEbobot(const std::shared_ptr<Storage>& storage, const std::shared_ptr<Log>& log):
	storage_(storage),log_(log)
{}

std::optional<std::string> ControllerEbobot::Handle(const User& user, const Group& group, const Command& command)
{
	
	if(command.command=="dick")
	{}
	else if (command.command=="start");
	else if (command.command=="top");

	return {};
}
