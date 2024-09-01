#include "ControllerEbobot.hpp"

ControllerEbobot::ControllerEbobot(const std::shared_ptr<Storage>& storage, const std::shared_ptr<Log>& log):
	storage_(storage),log_(log)
{}

std::string ControllerEbobot::Handle(const User& user, const Group& group, const Command& command)
{
	return "Hello\n";
}
