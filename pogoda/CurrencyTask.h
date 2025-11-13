#pragma once
#include <vector>
#include <string>
#include "ITask.h"

class ITimer;
class IDatabaseEngine;
class IHttpPoller;

class CurrencyTask : public ITask
{
public:
	CurrencyTask(const std::vector<std::string>& codes, std::unique_ptr<ITimer> timer, const std::string& historyDays, std::unique_ptr<IDatabaseEngine> databaseEngine, std::unique_ptr<IHttpPoller> poller);
protected:
	void Execute() override;
private:
	void CreateUrls(const std::vector<std::string>& codes) const;
	std::unique_ptr<ITimer> timer_;
	const std::vector<std::string> codes_;
	std::vector<std::string> urls_;
	std::string historyDays_;
	std::unique_ptr<IDatabaseEngine> databaseEngine_;
	std::unique_ptr<IHttpPoller> poller_;
};

