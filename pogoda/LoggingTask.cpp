#include "LoggingTask.h"
#include "ITimer.h"
#include "Logger.h"

LoggingTask::LoggingTask(std::unique_ptr<ITimer> timer) :
	timer_(std::move(timer))
{
}

void LoggingTask::Execute()
{
	while (running_)
	{
		if(timer_->ShouldTick())
		{
			//
		}
		SleepForMilliseconds(100);
	}
}
