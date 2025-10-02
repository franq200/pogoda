#include "TimeProvider.h"

CurrentTime TimeProvider::GetCurrentTime()
{
	CurrentTime currentTime;
	currentTime.year = GetCurrentYear();
	currentTime.month = GetCurrentMonth();
	currentTime.day = GetCurrentDay();
	currentTime.hour = GetCurrentHour();
	currentTime.minute = GetCurrentMinute();
	currentTime.second = GetCurrentSecond();

	uint64_t ms = GetMillisecondsSinceEpoch();
	currentTime.millisecond = std::to_string(ms % 1000);
	currentTime.millisecondsSinceEpoch = std::to_string(ms);
	return currentTime;
}

std::string TimeProvider::GetCurrentTimeString()
{
	CurrentTime currentTime = GetCurrentTime();
	return currentTime.year + "-" + currentTime.month + "-" + currentTime.day + " " +
		currentTime.hour + ":" + currentTime.minute + ":" + currentTime.second + "." + currentTime.millisecond;
}

std::string TimeProvider::GetCurrentDay()
{
	auto currentTimeChrono_ = std::chrono::system_clock::now();
	auto currentDateChrono_ = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTimeChrono_));
	return std::to_string(static_cast<unsigned int>(currentDateChrono_.day()));
}

std::string TimeProvider::GetCurrentMonth()
{
	auto currentTimeChrono_ = std::chrono::system_clock::now();
	auto currentDateChrono_ = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTimeChrono_));
	return std::to_string(static_cast<unsigned int>(currentDateChrono_.month()));
}

std::string TimeProvider::GetCurrentYear()
{
	auto currentTimeChrono_ = std::chrono::system_clock::now();
	auto currentDateChrono_ = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTimeChrono_));
	return std::to_string(static_cast<int>(currentDateChrono_.year()));
}

std::string TimeProvider::GetCurrentHour()
{
	auto currentTimeChrono_ = std::chrono::system_clock::now();
	return std::to_string(std::chrono::time_point_cast<std::chrono::hours>(currentTimeChrono_).time_since_epoch().count() % 24);
}

std::string TimeProvider::GetCurrentMinute()
{
	auto currentTimeChrono_ = std::chrono::system_clock::now();
	return std::to_string(std::chrono::time_point_cast<std::chrono::minutes>(currentTimeChrono_).time_since_epoch().count() % 60);
}

std::string TimeProvider::GetCurrentSecond()
{
	auto currentTimeChrono_ = std::chrono::system_clock::now();
	return std::to_string(std::chrono::time_point_cast<std::chrono::seconds>(currentTimeChrono_).time_since_epoch().count() % 60);
}

uint64_t TimeProvider::GetMillisecondsSinceEpoch()
{
	auto currentTimeChrono_ = std::chrono::system_clock::now();
	return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(currentTimeChrono_.time_since_epoch()).count());
}
