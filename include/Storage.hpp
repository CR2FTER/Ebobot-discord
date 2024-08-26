#pragma once
#include <vector>
#include <optional>
#include "TimeSet.hpp"
#include "User.hpp"
#include "Group.hpp"
#include "Data.hpp"
class Storage
{
public:
	virtual std::optional<std::tuple<TimeSet, Data>> getUser(const User&, const Group&) = 0;
	virtual std::vector<std::tuple<TimeSet, Data, User>> getAllUsersFromGroup(const Group&) = 0;
	virtual void setValue(const User&, const Group&, const Data&) = 0;
};

