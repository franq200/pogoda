#pragma once
#include <chrono>
#include <string>

struct CurrentTime
{
	std::string year;
	std::string month;
	std::string day;
	std::string hour;
	std::string minute;
	std::string second;
	std::string millisecond;
	std::string millisecondsSinceEpoch;
};

class TimeProvider
{
public:
	static CurrentTime GetCurrentTime();
	static std::string GetCurrentTimeString();
	static std::string GetCurrentDay();
	static std::string GetCurrentMonth();
	static std::string GetCurrentYear();
	static std::string GetCurrentHour();
	static std::string GetCurrentMinute();
	static std::string GetCurrentSecond();
	static uint64_t GetMillisecondsSinceEpoch();
};

