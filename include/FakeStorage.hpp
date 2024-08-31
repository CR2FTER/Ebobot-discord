#pragma once
#include "Storage.hpp"

class FakeStorage : public Storage
{
public:
	std::optional<std::tuple<TimeSet, Data>> getUser(const User&, const Group&) const  override;	
	std::vector<std::tuple<Data, User>> getAllUsersFromGroup(const Group&) override;
	void setValue(const User&, const Group&, const Data&) override;
	std::vector<std::tuple<Data, User>> getLimitTopUsersFromGroup(const Group&, std::size_t count) override;
	std::vector<std::tuple<Data, User, Group>> getLimitTopUsersFromAllGroup(std::size_t count) override;
};
