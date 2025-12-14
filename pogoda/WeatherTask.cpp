#include "WeatherTask.h"
#include "ITimer.h"
#include "WeatherHttpPoller.h"
#include "IHttpPoller.h"
#include "IDatabaseEngine.h"

WeatherTask::WeatherTask(const std::vector<std::string>& cities, std::unique_ptr<IHttpPoller> poller, std::unique_ptr<ITimer> timer, std::shared_ptr<IDatabaseEngine> databaseEngine) :
	poller_(std::move(poller)), timer_(std::move(timer)), databaseEngine_(std::move(databaseEngine))
{
	CreateUrls(cities);
}

void WeatherTask::Execute()
{
	while (running_)
	{
		if(timer_->ShouldTick())
		{
			std::vector<std::unique_ptr<WeatherData>> polledData;
			for (const auto& url : urls_)
			{
				WeatherRequest request;
				request.url = url;
				auto data = poller_->Poll(request);
				if (data != nullptr)
				{
					std::unique_ptr<WeatherData> weatherData(static_cast<WeatherData*>(data.release()));
					polledData.emplace_back(std::move(weatherData));
				}
			}

			for (const auto& data : polledData)
			{
				std::string query =
					"INSERT INTO WeatherData (Location, CurrentTime, Temperature, Humidity, WindSpeed) "
					"VALUES ("
					"'" + data->location + "', "
					"'" + data->localTime + "', "
					"'" + data->temperature + "', "
					"'" + data->humidity + "', "
					"'" + data->windSpeed + "')";

				databaseEngine_->executeQuery(query);
			}

		}
		SleepForMilliseconds(100);
	}
}

void WeatherTask::CreateUrls(const std::vector<std::string>& cities)
{
	urls_.clear();
	urls_.reserve(cities.size());

	std::string baseUrl = "https://wttr.in/";
	std::string format = "?format=j1";

	for (const auto& city : cities)
	{
		urls_.push_back(baseUrl + city + format);
	}
}
