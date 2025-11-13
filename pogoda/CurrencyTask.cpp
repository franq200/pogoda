#include "CurrencyTask.h"
#include "ITimer.h"
#include "IDatabaseEngine.h"
#include "CurrencyPoller.h"

CurrencyTask::CurrencyTask(const std::vector<std::string>& codes, std::unique_ptr<ITimer> timer, const std::string& historyDays, std::unique_ptr<IDatabaseEngine> databaseEngine, std::unique_ptr<IHttpPoller> poller)
	: timer_(std::move(timer)), historyDays_(historyDays), databaseEngine_(std::move(databaseEngine)), poller_(std::move(poller))
{
	CreateUrls(codes);
}

void CurrencyTask::Execute()
{
	while (running_)
	{
		if (timer_->ShouldTick())
		{
			std::vector<std::unique_ptr<CurrencyData>> polledData;
			for (const auto& url : urls_)
			{
				auto data = poller_->Poll(url);
				if (data != nullptr)
				{
					std::unique_ptr<CurrencyData> weatherData(static_cast<CurrencyData*>(data.release()));
					polledData.emplace_back(std::move(weatherData));
				}
			}

			for (const auto& data : polledData)
			{
				for (const auto& rate : data->rates)
				{
					std::string query =
						"INSERT INTO CurrencyRates (Code, Time, BidPrice, AskPrice) "
						"VALUES ("
						"'" + data->code + "', "
						"'" + rate.time + "', "
						"'" + rate.bidPrice + "', "
						"'" + rate.askPrice + "')";
					
					databaseEngine_->executeQuery(query);
				}
			}

		}
		SleepForMilliseconds(100);
	}
}

void CurrencyTask::CreateUrls(const std::vector<std::string>& codes) const
{
	return;
}