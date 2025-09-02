#pragma once
#include <chrono>

class Timer
{
public:
	Timer(int intervalSeconds);
	bool ShouldTick();
private:
	std::chrono::duration<double> interval_;
	std::chrono::steady_clock::time_point lastTick_;
};

