#include "Timer.h"

Timer::Timer(int intervalSeconds):
	interval_(std::chrono::duration<double>(intervalSeconds)), lastTick_(std::chrono::steady_clock::now())
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
