#include "CurrencyTask.h"
#include "ITimer.h"
#include "IDatabaseEngine.h"
#include "CurrencyPoller.h"
#include <format>
#include <algorithm>

CurrencyTask::CurrencyTask(const std::vector<std::string>& codes, std::unique_ptr<ITimer> timer, const std::string& historyDays, std::shared_ptr<IDatabaseEngine> databaseEngine, std::unique_ptr<IHttpPoller> poller)
	: timer_(std::move(timer)), historyDays_(historyDays), databaseEngine_(std::move(databaseEngine)), poller_(std::move(poller)), codes_(codes)
{}

void CurrencyTask::Execute()
{
	while (running_)
	{
		if (timer_->ShouldTick())
		{
			std::vector<std::unique_ptr<CurrencyResponse>> polledData;
			std::vector<CurrencyRequest> requests = PrepareRequests();
			for (const auto& request : requests)
			{
				auto data = poller_->Poll(request);
				if (data != nullptr)
				{
					std::unique_ptr<CurrencyResponse> weatherData(static_cast<CurrencyResponse*>(data.release()));
					polledData.emplace_back(std::move(weatherData));
				}
			}

			for (const auto& data : polledData)
			{
				for (const auto& rate : data->rates)
				{
					std::string query =
						"INSERT INTO Currency (Code, Time, BidPrice, AskPrice) "
						"VALUES ("
						"'" + data->code + "', "
						"'" + rate.time + "', "
						"'" + rate.bidPrice == "" ? "NULL" : rate.bidPrice + "', "
						"'" + rate.askPrice == "" ? "NULL" : rate.askPrice + "')";
					
					databaseEngine_->executeQuery(query);
				}
			}

		}
		SleepForMilliseconds(100);
	}
}

CurrencyRequest CurrencyTask::CreateRequestData(const std::string& code, const std::string& firstDay, const std::string& lastDay)
{
	std::string baseUrl = "https://api.nbp.pl/api/exchangerates/rates/C/";
	std::string format = "/" + firstDay + "/" + lastDay + "/?format=json";

	CurrencyRequest request;
	request.code = code;
	request.firstDay = firstDay;
	request.lastDay = lastDay;
	request.url = baseUrl + code + format;

	return request;
}

std::vector<CurrencyRequest> CurrencyTask::PrepareRequests()
{
	std::vector<CurrencyRequest> requests;
	for (const auto& code : codes_)
	{
		std::chrono::year_month_day currentDay = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
		std::chrono::sys_days oldestDate = std::chrono::sys_days(currentDay) - std::chrono::days(std::stoi(historyDays_));
		std::chrono::sys_days oldestDateCopy = oldestDate;
		std::chrono::year_month_day formatedDate = std::chrono::year_month_day{ oldestDate };
		std::vector<std::chrono::sys_days> savedDates = GetSavedDates(code, formatedDate);

		std::vector<std::pair<std::chrono::sys_days, std::chrono::sys_days>> dateRanges;

		while (currentDay >= oldestDateCopy)
		{
			// 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17
			// x     x x w w    x  x        w   w
			/*
			1: 4-5
			2: 10-10
			3: 13-14
			4: 17-17
			*/
			if (std::none_of(savedDates.begin(), savedDates.end(), [&oldestDateCopy](const auto& el) {return el == oldestDateCopy; }))
			{
				std::chrono::weekday weekday = std::chrono::weekday(oldestDateCopy);
				if (weekday != std::chrono::Saturday && weekday != std::chrono::Sunday)
				{
					const bool stillLastRange = !dateRanges.empty() && dateRanges.back().second == oldestDateCopy - std::chrono::days(1);
					if (stillLastRange)
					{
						dateRanges.back().second = oldestDateCopy;
					}
					else
					{
						std::pair<std::chrono::sys_days, std::chrono::sys_days> newRange(oldestDateCopy, oldestDateCopy);
						dateRanges.push_back(newRange);
					}
				}
			}
			oldestDateCopy += std::chrono::days(1);
		}

		for (const auto& range : dateRanges)
		{
			std::chrono::year_month_day ymdFirst{ range.first };
			std::chrono::year_month_day ymdLast{ range.second };

			auto last = std::format("{:%Y-%m-%d}", ymdLast);
			auto first = std::format("{:%Y-%m-%d}", ymdFirst);

			requests.push_back(CreateRequestData(code, first, last));
		}
	}
	return requests;
}

std::vector<std::chrono::sys_days> CurrencyTask::GetSavedDates(const std::string& code, const std::chrono::year_month_day& formatedDate)
{
	std::string formatedDateString = std::format("{:04}-{:02}-{:02}", static_cast<int>(formatedDate.year()), static_cast<unsigned>(formatedDate.month()), static_cast<unsigned>(formatedDate.day()));
	std::string query = 
		"SELECT DISTINCT Time FROM Currency WHERE Code == '" + code + "'" "AND Time >= '" + formatedDateString + "'";
	databaseEngine_->executeQuery(query);

	std::vector<std::vector<std::string>> results = databaseEngine_->getResults(std::this_thread::get_id());
	std::vector<std::chrono::sys_days> savedDates;
	savedDates.reserve(results.size());
	for (const auto& row : results)
	{
		if (!row.empty())
		{
			std::istringstream dateStringStream(row[0]);
			std::chrono::year_month_day ymd;
			dateStringStream >> std::chrono::parse("%Y-%m-%d", ymd);
			savedDates.push_back(std::chrono::sys_days{ ymd });
		}
	}
	return savedDates;
}
