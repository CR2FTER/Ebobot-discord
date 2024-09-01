#include <atomic>

class SpinLock
{
public:
	void lock() noexcept;
	bool try_lock() noexcept;
	void unlock() noexcept;
private:
	std::atomic<bool> flag_ = false;
};
