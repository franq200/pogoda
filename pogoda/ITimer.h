#pragma once
class ITimer
{
public:
	virtual ~ITimer() = default;
	virtual bool ShouldTick() = 0;
};

