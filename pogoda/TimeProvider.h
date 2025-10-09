#pragma once
#include <chrono>
#include "ITimeProvider.h"

class TimeProvider : public ITimeProvider
{
public:
	~TimeProvider() override = default;
	CurrentTime GetCurrentTime() override;
	std::string GetCurrentTimeString() override;
	std::string GetCurrentDay() override;
	std::string GetCurrentMonth() override;
	std::string GetCurrentYear() override;
	std::string GetCurrentHour() override;
	std::string GetCurrentMinute() override;
	std::string GetCurrentSecond() override;
	uint64_t GetMillisecondsSinceEpoch() override;
private:
	CurrentTime currentTime_;
	std::chrono::system_clock::time_point currentTimeChrono_;
	std::chrono::year_month_day currentDateChrono_;
};

