#include "WeatherTask.h"
#include "ITimer.h"
#include "WeatherHttpPoller.h"
#include "IHttpPoller.h"
#include "IDatabaseEngine.h"

WeatherTask::WeatherTask(std::vector<std::string> urls, std::unique_ptr<IHttpPoller> poller, std::unique_ptr<ITimer> timer, std::unique_ptr<IDatabaseEngine> databaseEngine) :
	urls_(std::move(urls)), poller_(std::move(poller)), timer_(std::move(timer)), databaseEngine_(std::move(databaseEngine))
{
}

void WeatherTask::Execute()
{
	while (running_)
	{
		if(timer_->ShouldTick())
		{
			std::vector<WeatherData> polledData;
			for (const auto& url : urls_)
			{
				polledData.push_back(poller_->Poll(url));
			}

			for (const auto& data : polledData)
			{
				std::string query =
					"INSERT INTO WeatherData (Location, CurrentTime, Temperature, Humidity, WindSpeed) "
					"VALUES ("
					"'" + data.location + "', "
					"datetime('now'), "
					"'" + data.temperature + "', "
					"'" + data.humidity + "', "
					"'" + data.windSpeed + "');";

				databaseEngine_->executeQuery(query);
			}

		}
		SleepForMilliseconds(100);
	}
}
