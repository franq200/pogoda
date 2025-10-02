#pragma once
#include <thread>

class ITask
{
public:
	virtual ~ITask() = default;
	void Start();
	void Stop();
	void Join();
protected:
	void SleepForMilliseconds(int milliseconds) const;
	virtual void Execute() = 0;
	std::thread thread_;
	std::atomic<bool> running_ = false;
};

