#include "ITask.h"
#include "Logger.h"

void ITask::Start()
{
	if (thread_.joinable())
	{
		Logger::GetInstance()->LogWarning("Task is already running. Restarting the task.");
		Stop();
		Join();
	}
	running_ = true;
	thread_ = std::thread(&ITask::Execute, this);
}

void ITask::Stop()
{
	running_ = false;
}

void ITask::Join()
{
	if (thread_.joinable())
	{
		thread_.join();
	}
}

void ITask::SleepForMilliseconds(int milliseconds) const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
