#include "TimeSet.hpp"
#include <chrono>

TimeSet::TimeSet() noexcept:
	time_(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{}

TimeSet::TimeSet(std::uint64_t time) noexcept: time_(time)
{}

TimeSet::operator std::uint64_t() const noexcept
{
	return time_;
}
