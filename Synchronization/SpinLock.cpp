#include "SpinLock.hpp"

void SpinLock::lock() noexcept
{
	bool tmp;
	{
		tmp = false;
	}while(!flag_.compare_exchange_weak(tmp, true, std::memory_order_acquire, std::memory_order_relaxed));
}

bool SpinLock::try_lock() noexcept
{
	bool tmp = false;
	return flag_.compare_exchange_weak(tmp, true, std::memory_order_acquire, std::memory_order_relaxed); 
}

void SpinLock::unlock() noexcept
{
	flag_.store(false, std::memory_order_release);
}
