#pragma once
#include <chrono>

class Timer
{
public:
	Timer(uint64_t intervalSeconds);
	bool ShouldTick();
private:
	std::chrono::steady_clock::duration interval_;
	std::chrono::steady_clock::time_point lastTick_;
};

