#include "Timer.h"

Timer::Timer(uint64_t intervalSeconds):
	interval_(std::chrono::seconds(intervalSeconds)),
	lastTick_(std::chrono::steady_clock::now() - interval_)
{
}

bool Timer::ShouldTick()
{
	auto now = std::chrono::steady_clock::now();
	auto sinceLastTick = now - lastTick_;
	if (sinceLastTick >= interval_)
	{
		lastTick_ = now;
		return true;
	}
	return false;
}
