#include "CurrencyPoller.h"
#include "IDataParser.h"
#include "Logger.h"
#include <iostream>

CurrencyPoller::CurrencyPoller(std::unique_ptr<IDataParser<CurrencyData>> dataParser)
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

std::unique_ptr<IHttpPoller::PollResult> CurrencyPoller::Poll(const std::string& url)
{
	auto logger = Logger::GetInstance();
	std::string response;
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());

	CURLcode res = curl_easy_perform(curl_);
	if (res != CURLE_OK)
	{
		logger->LogError("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
		return {};
	}
	response_ = std::make_unique<CurrencyData>(dataParser_->Deserialize(response));

	for (const auto& rate : response_->rates)
	{
		logger->LogInfo( "Code: " + response_->code + 
			"Time: " + rate.time +
			"Ask Price: " + rate.askPrice +
			"Bid Price: " + rate.bidPrice);
		std::cerr << "Code: " << response_->code <<
			"Time: " << rate.time <<
			"Ask Price: " << rate.askPrice <<
			"Bid Price: " << rate.bidPrice;
	}

	return std::move(response_);
}
