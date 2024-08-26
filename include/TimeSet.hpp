#pragma once
#include <cstdint>

class TimeSet
{
public:
	TimeSet() noexcept;
	TimeSet(std::uint64_t time) noexcept;
	operator std::uint64_t() const noexcept;
private:
	std::uint64_t time_;
};
