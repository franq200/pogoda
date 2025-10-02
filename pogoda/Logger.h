#pragma once  
#include <fstream>  
#include <memory>
#include <vector>
#include "ILogger.h"

class Logger : public ILogger  
{  
public:  
    ~Logger() override;
    Logger(const Logger&) = delete;  
    Logger& operator=(const Logger&) = delete;
	void LogCollectedLogs() override;

    static std::shared_ptr<Logger> GetInstance()
    {
        if (!instance_) 
        {
            instance_ = std::shared_ptr<Logger>(new Logger());
        }
        return instance_;
    }

private:
    Logger();  
	void CreateLogFile();
    static std::shared_ptr<Logger> instance_;
    static std::ofstream logFile_;
	std::string LastLogTime_;
    std::vector<std::string> collectedLogs_;
protected:  
    void Log(const std::string& message, LogLevel logLevel) override;  
};
