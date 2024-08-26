#include "TimeSet.hpp"
#include <ctime>

TimeSet::TimeSet() noexcept: time_(std::time(NULL))
{}

TimeSet::TimeSet(std::uint64_t time) noexcept: time_(time)
{}

TimeSet::operator std::uint64_t() const noexcept
{
	return time_;
}
