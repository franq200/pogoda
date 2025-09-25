#pragma once  
#include <fstream>  
#include <memory>
#include "ILogger.h"  

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
	CurrentTime LastLogTime_;

protected:  
    void Log(const std::string& message, LogLevel logLevel) override;  
};
