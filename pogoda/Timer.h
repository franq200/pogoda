#pragma once
#include <chrono>

#include "ITimer.h"

class Timer : public ITimer
{
public:
	Timer(uint64_t intervalSeconds);
	bool ShouldTick() override;
private:
	std::chrono::steady_clock::duration interval_;
	std::chrono::steady_clock::time_point lastTick_;
};

