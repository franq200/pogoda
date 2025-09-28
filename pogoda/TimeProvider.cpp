#include "TimeProvider.h"

CurrentTime TimeProvider::GetCurrentTime()
{
	currentTime_.year = GetCurrentYear();
	currentTime_.month = GetCurrentMonth();
	currentTime_.day = GetCurrentDay();
	currentTime_.hour = GetCurrentHour();
	currentTime_.minute = GetCurrentMinute();
	currentTime_.second = GetCurrentSecond();

	uint64_t ms = GetMillisecondsSinceEpoch();
	currentTime_.millisecond = std::to_string(ms % 1000);
	currentTime_.millisecondsSinceEpoch = std::to_string(ms);
	return currentTime_;
}

std::string TimeProvider::GetCurrentTimeString()
{
	CurrentTime currentTime = GetCurrentTime();
	return currentTime.year + "-" + currentTime.month + "-" + currentTime.day + " " +
		currentTime.hour + ":" + currentTime.minute + ":" + currentTime.second + "." + currentTime.millisecond;
}

std::string TimeProvider::GetCurrentDay()
{
	currentTimeChrono_ = std::chrono::system_clock::now();
	currentDateChrono_ = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTimeChrono_));
	return std::to_string(static_cast<unsigned int>(currentDateChrono_.day()));
}

std::string TimeProvider::GetCurrentMonth()
{
	currentTimeChrono_ = std::chrono::system_clock::now();
	currentDateChrono_ = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTimeChrono_));
	return std::to_string(static_cast<unsigned int>(currentDateChrono_.month()));
}

std::string TimeProvider::GetCurrentYear()
{
	currentTimeChrono_ = std::chrono::system_clock::now();
	currentDateChrono_ = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTimeChrono_));
	return std::to_string(static_cast<int>(currentDateChrono_.year()));
}

std::string TimeProvider::GetCurrentHour()
{
	currentTimeChrono_ = std::chrono::system_clock::now();
	return std::to_string(std::chrono::time_point_cast<std::chrono::hours>(currentTimeChrono_).time_since_epoch().count() % 24);
}

std::string TimeProvider::GetCurrentMinute()
{
	currentTimeChrono_ = std::chrono::system_clock::now();
	return std::to_string(std::chrono::time_point_cast<std::chrono::minutes>(currentTimeChrono_).time_since_epoch().count() % 60);
}

std::string TimeProvider::GetCurrentSecond()
{
	currentTimeChrono_ = std::chrono::system_clock::now();
	return std::to_string(std::chrono::time_point_cast<std::chrono::seconds>(currentTimeChrono_).time_since_epoch().count() % 60);
}

uint64_t TimeProvider::GetMillisecondsSinceEpoch()
{
	currentTimeChrono_ = std::chrono::system_clock::now();
	return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(currentTimeChrono_.time_since_epoch()).count());
}
