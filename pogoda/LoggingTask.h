#pragma once
#include "ITask.h"

class ITimer;
class ILogger;

class LoggingTask : public ITask
{
public:
	LoggingTask(std::unique_ptr<ITimer> timer, std::shared_ptr<ILogger> logger);
protected:
	void Execute() override;
private:
	std::shared_ptr<ILogger> logger_;
	std::unique_ptr<ITimer> timer_;
};

