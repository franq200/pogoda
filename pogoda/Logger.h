#pragma once  
#include <fstream>  
#include "ILogger.h"  

struct CurrentTime
{
    std::string year;
    std::string month;
    std::string day;
    std::string hour;
    std::string minute;
    std::string second;
    std::string timeSinceEpoch;
};

class Logger : public ILogger  
{  
public:  
    Logger(const Logger&) = delete;  
    Logger& operator=(const Logger&) = delete;  

    static Logger* GetInstance()
    {
        if (!instance_) 
        {
            instance_ = std::unique_ptr<Logger>(new Logger());
        }
        return instance_.get();
    }
private:  
	CurrentTime GetCurrentTime() const;
    Logger();  
    static std::unique_ptr<Logger> instance_;  
    static std::ofstream logFile_;  

protected:  
    void Log(const std::string& message, LogLevel logLevel) const override;  
};
