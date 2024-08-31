#pragma once
#include <vector>
#include <optional>
#include <tuple>
#include "TimeSet.hpp"
#include "User.hpp"
#include "Group.hpp"
#include "Data.hpp"
class Storage
{
public:
	virtual std::optional<std::tuple<TimeSet, Data>> getUser(const User&, const Group&) const = 0;
	virtual std::vector<std::tuple<Data, User>> getAllUsersFromGroup(const Group&) = 0;
	virtual void setValue(const User&, const Group&, const Data&) = 0;
	virtual std::vector<std::tuple<Data, User>> getLimitTopUsersFromGroup(const Group&, std::size_t count) = 0;
	virtual std::vector<std::tuple<Data, User, Group>> getLimitTopUsersFromAllGroup(std::size_t count) = 0;
};

