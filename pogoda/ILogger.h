#pragma once
#include <string>

class ILogger
{
public:
	virtual ~ILogger() = default;
	void LogError(const std::string& message) const;
	void LogWarning(const std::string& message) const;
	void LogInfo(const std::string& message) const;

	[[noreturn]] void LogCriticalError(const std::string& message) const;
protected:
	enum class LogLevel
	{
		Error = 0,
		Warning,
		Info
	};
	virtual void Log(const std::string& message, LogLevel logLevel) const = 0;
};

