#include "LoggingTask.h"
#include "ITimer.h"
#include "ILogger.h"

LoggingTask::LoggingTask(std::unique_ptr<ITimer> timer, std::shared_ptr<ILogger> logger) :
	timer_(std::move(timer)), logger_(std::move(logger))
{
}

void LoggingTask::Execute()
{
	while (running_)
	{
		if(timer_->ShouldTick())
		{
			logger_->LogCollectedLogs();
		}
		SleepForMilliseconds(100);
	}
}
