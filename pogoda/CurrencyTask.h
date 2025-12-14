#pragma once
#include <vector>
#include <string>
#include <chrono>
#include "ITask.h"
#include "IHttpPoller.h"

class ITimer;
class IDatabaseEngine;

struct CurrencyRequest : public IHttpPoller::PollRequest
{
	std::string url;
	std::string code;
	std::string firstDay;
	std::string lastDay;
};;

class CurrencyTask : public ITask
{
public:
	CurrencyTask(const std::vector<std::string>& codes, std::unique_ptr<ITimer> timer, const std::string& historyDays, std::shared_ptr<IDatabaseEngine> databaseEngine, std::unique_ptr<IHttpPoller> poller);
protected:
	void Execute() override;
private:
	CurrencyRequest CreateRequestData(const std::string& code, const std::string& firstDay, const std::string& lastDay);
	std::vector<CurrencyRequest> PrepareRequests();
	std::vector<std::chrono::sys_days> GetSavedDates(const std::string& code, const std::chrono::year_month_day& formatedDate);
	std::unique_ptr<ITimer> timer_;
	const std::vector<std::string> codes_;
	std::string historyDays_;
	std::shared_ptr<IDatabaseEngine> databaseEngine_;
	std::unique_ptr<IHttpPoller> poller_;
};

