#pragma once
#include "IHttpPoller.h"

#include <string>
#include <curl/curl.h>
#include <memory>
#include <nlohmann/json.hpp>

template <typename T>
class IDataParser;

struct Rate
{
	std::string time;
	std::string askPrice;
	std::string bidPrice;
};

struct CurrencyResponse : public IHttpPoller::PollResult
{
	std::string code;
	std::vector<Rate> rates;
};

inline void from_json(const nlohmann::json& j, Rate& d)
{
	d.time = j.at("effectiveDate").get<std::string>();
	d.askPrice = std::to_string(j.at("ask").get<double>());
	d.bidPrice = std::to_string(j.at("bid").get<double>());
}

inline void from_json(const nlohmann::json& j, CurrencyResponse& d)
{
	d.code = j.at("code").get<std::string>();
	d.rates = j.at("rates").get<std::vector<Rate>>();
}

inline void to_json(nlohmann::json& j, const Rate& d)
{
	j = nlohmann::json
	{
		nlohmann::json::array({nlohmann::json{
				{"effectiveDate", d.time},
				{"ask", d.askPrice},
				{"bid", d.bidPrice},}})
	};
}

inline void to_json(nlohmann::json& j, const CurrencyResponse& d)
{
	j = nlohmann::json
	{
		nlohmann::json::array({nlohmann::json{
				{"code", d.code},
				{"rates", d.rates},}})
	};
}
 
class CurrencyPoller : public IHttpPoller
{
public:
	CurrencyPoller(std::unique_ptr<IDataParser<CurrencyResponse>> dataParser);
	~CurrencyPoller() override;
	std::unique_ptr<PollResult> Poll(const PollRequest& request) override;
private:
	CURL* curl_;
	std::unique_ptr<CurrencyResponse> response_;
	std::unique_ptr<IDataParser<CurrencyResponse>> dataParser_;
};

