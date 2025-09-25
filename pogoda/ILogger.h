#pragma once
#include <string>

class ILogger
{
public:
	virtual ~ILogger() = default;
	void LogError(const std::string& message);
	void LogWarning(const std::string& message);
	void LogInfo(const std::string& message);

	[[noreturn]] void LogCriticalError(const std::string& message);
protected:
	enum class LogLevel
	{
		Error = 0,
		Warning,
		Info
	};
	virtual void Log(const std::string& message, LogLevel logLevel) = 0;
};

