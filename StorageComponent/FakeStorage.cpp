#include "FakeStorage.hpp"

FakeStorage::FakeStorage(const std::shared_ptr<Log>& log) : log_(log)
{}

std::optional<std::tuple<TimeSet, Data>> FakeStorage::getUser(const User&, const Group&) const
{
	return {};
}

std::vector<std::tuple<Data, User>> FakeStorage::getAllUsersFromGroup(const Group&)
{
	return {};
}

void FakeStorage::setValue(const User&, const Group&, const Data&)
{

}

std::vector<std::tuple<Data, User>> FakeStorage::getLimitTopUsersFromGroup(const Group&, std::size_t count)
{
	return {};
}

std::vector<std::tuple<Data, User, Group>> FakeStorage::getLimitTopUsersFromAllGroup(std::size_t count)
{
	return {};
}
