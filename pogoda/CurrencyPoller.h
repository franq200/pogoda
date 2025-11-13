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

struct CurrencyData : public IHttpPoller::PollResult
{
	std::string code;
	std::vector<Rate> rates;
};

inline void from_json(const nlohmann::json& j, CurrencyData& d)
{
	d.code = j.at("current_condition")[0].at("windspeedKmph").get<std::string>();
	d.rates = j.at("current_condition")[0].at("temp_C").get<std::string>();
}
inline void to_json(nlohmann::json& j, const CurrencyData& d)
{
	j = nlohmann::json
	{
		{"current_condition", nlohmann::json::array({nlohmann::json{
				{"windspeedKmph", d.code},
				{"temp_C", d.rates},}})}
	};
}

inline void from_json(const nlohmann::json& j, Rate& d)
{
	d.time = j.at("current_condition")[0].at("windspeedKmph").get<std::string>();
	d.askPrice = j.at("current_condition")[0].at("temp_C").get<std::string>();
	d.bidPrice = j.at("current_condition")[0].at("temp_C").get<std::string>();
}
inline void to_json(nlohmann::json& j, const Rate& d)
{
	j = nlohmann::json
	{
		{"current_condition", nlohmann::json::array({nlohmann::json{
				{"windspeedKmph", d.time},
				{"temp_C", d.askPrice},
				{"humidity", d.bidPrice},}})}
	};
}
 
class CurrencyPoller : public IHttpPoller
{
public:
	CurrencyPoller(std::unique_ptr<IDataParser<CurrencyData>> dataParser);
	~CurrencyPoller() override;
	std::unique_ptr<PollResult> Poll(const std::string& url) override;
private:
	CURL* curl_;
	std::unique_ptr<CurrencyData> response_;
	std::unique_ptr<IDataParser<CurrencyData>> dataParser_;
};

