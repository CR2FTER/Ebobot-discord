#pragma once
#include <vector>
#include <optional>
#include "TimeSet.hpp"
#include "User.hpp"
#include "Group.hpp"
#include "Data.hpp"
class Storage
{
	virtual std::optional<std::tuple<TimeSet, Data>> getUser(User, Group) = 0;
	virtual std::vector<std::tuple<TimeSet, Data, User>> getAllUsersFromGroup(Group) = 0;
};

