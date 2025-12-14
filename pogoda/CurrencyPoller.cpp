#include "CurrencyPoller.h"
#include "IDataParser.h"
#include "Logger.h"
#include <iostream>
#include "CurrencyTask.h"

CurrencyPoller::CurrencyPoller(std::unique_ptr<IDataParser<CurrencyResponse>> dataParser)
	: dataParser_(std::move(dataParser))
{
	curl_ = curl_easy_init();
	if (!curl_)
	{
		throw std::runtime_error("Failed to initialize Currency CURL");
	}
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, IHttpPoller::WriteCallback);
}

CurrencyPoller::~CurrencyPoller()
{
	if (curl_)
	{
		curl_easy_cleanup(curl_);
	}
}

std::unique_ptr<IHttpPoller::PollResult> CurrencyPoller::Poll(const PollRequest& request)
{
	const CurrencyRequest& currencyRequest = static_cast<const CurrencyRequest&>(request);
	auto logger = Logger::GetInstance();
	std::string response;
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl_, CURLOPT_URL, currencyRequest.url.c_str());

	CURLcode res = curl_easy_perform(curl_);
	if (res != CURLE_OK)
	{
		logger->LogError("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
		return {};
	}
	if (response.starts_with("404"))
	{
		logger->LogWarning("Currency data not found for URL: " + currencyRequest.url);
		CurrencyResponse emptyData;
		emptyData.code = currencyRequest.code;
		std::chrono::sys_days lastDay;
		std::istringstream(currencyRequest.lastDay) >> std::chrono::parse("%F", lastDay);
		std::chrono::sys_days firstDay;
		std::istringstream(currencyRequest.firstDay) >> std::chrono::parse("%F", firstDay);

		for (;firstDay <= lastDay; firstDay += std::chrono::days{ 1 })
		{
			std::chrono::year_month_day ymd = std::chrono::year_month_day{ firstDay };
			Rate rate;
			rate.time = std::format("{:04}-{:02}-{:02}", static_cast<int>(ymd.year()), static_cast<unsigned>(ymd.month()), static_cast<unsigned>(ymd.day()));
			rate.askPrice = "";
			rate.bidPrice = "";
			emptyData.rates.push_back(rate);
		}
		response_ = std::make_unique<CurrencyResponse>(emptyData);
	}
	else
	{
		response_ = std::make_unique<CurrencyResponse>(dataParser_->Deserialize(response));
	}

	for (const auto& rate : response_->rates)
	{
		logger->LogInfo( "Code: " + response_->code + 
			"Time: " + rate.time +
			"Ask Price: " + rate.askPrice +
			"Bid Price: " + rate.bidPrice);
		std::cout << "Code: " << response_->code <<
			"Time: " << rate.time <<
			"Ask Price: " << rate.askPrice <<
			"Bid Price: " << rate.bidPrice;
	}

	return std::move(response_);
}
