#pragma once
#include <fstream>
#include "ILogger.h"

class Logger : public ILogger
{
public:
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	void Log(const std::string& message, LogLevel logLevel) const override;
private:
	Logger();
	static std::ofstream logFile_;
};

