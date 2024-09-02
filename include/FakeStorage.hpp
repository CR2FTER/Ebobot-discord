#pragma once
#include <memory>
#include "Log.hpp"
#include "Storage.hpp"

class FakeStorage : public Storage
{
public:
	FakeStorage(const std::shared_ptr<Log>&);
	std::optional<std::tuple<TimeSet, Data>> getUser(const User&, const Group&) const  override;	
	std::vector<std::tuple<Data, User>> getAllUsersFromGroup(const Group&) override;
	void setValue(const User&, const Group&, const Data&) override;
	std::vector<std::tuple<Data, User>> getLimitTopUsersFromGroup(const Group&, std::size_t count) override;
	std::vector<std::tuple<Data, User, Group>> getLimitTopUsersFromAllGroup(std::size_t count) override;
	void flush() const noexcept override;
private:
	std::shared_ptr<Log> log_;
};
