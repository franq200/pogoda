#pragma once
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

class ITimeProvider
{
public:
	virtual ~ITimeProvider() = default;
	virtual CurrentTime GetCurrentTime() = 0;
	virtual std::string GetCurrentTimeString() = 0;
	virtual std::string GetCurrentDay() = 0;
	virtual std::string GetCurrentMonth() = 0;
	virtual std::string GetCurrentYear() = 0;
	virtual std::string GetCurrentHour() = 0;
	virtual std::string GetCurrentMinute() = 0;
	virtual std::string GetCurrentSecond() = 0;
	virtual uint64_t GetMillisecondsSinceEpoch() = 0;
};

