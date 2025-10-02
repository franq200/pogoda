#pragma once
#include "ITask.h"

class ITimer;

class LoggingTask : public ITask
{
public:
	LoggingTask(std::unique_ptr<ITimer> timer);
protected:
	void Execute() override;
private:
	std::unique_ptr<ITimer> timer_;
};

