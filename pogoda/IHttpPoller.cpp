#include "IHttpPoller.h"

IHttpPoller::IHttpPoller(const std::string& url, int intervalSeconds, IDataParser<WeatherData>& dataParser):
	url_(url), intervalSeconds_(intervalSeconds), dataParser_(dataParser)
{
}
