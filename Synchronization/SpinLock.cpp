#include "SpinLock.hpp"
#include <iostream>

void SpinLock::lock() noexcept
{
	bool tmp;
	do{
		tmp = false;
	}
	while(!flag_.compare_exchange_weak(tmp, true, std::memory_order_seq_cst, std::memory_order_seq_cst));
	
}

bool SpinLock::try_lock() noexcept
{
	bool tmp = false; 
	return flag_.compare_exchange_weak(tmp, true, std::memory_order_seq_cst, std::memory_order_seq_cst); 
}

void SpinLock::unlock()  noexcept
{
	flag_.store(false, std::memory_order_seq_cst);
}
