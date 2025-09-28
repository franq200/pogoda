#pragma once  
#include <fstream>  
#include <memory>
#include "ILogger.h"
#include "TimeProvider.h"

class ITimeProvider;

class Logger : public ILogger  
{  
public:  
    ~Logger() override;
    Logger(const Logger&) = delete;  
    Logger& operator=(const Logger&) = delete;  

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
	TimeProvider timeProvider_;

protected:  
    void Log(const std::string& message, LogLevel logLevel) override;  
};
