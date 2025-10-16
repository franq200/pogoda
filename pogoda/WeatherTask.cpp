#include "WeatherTask.h"
#include "ITimer.h"
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
			for (const auto& url : urls_)
			{
				poller_->Poll(url); // przekazywaæ
			}
		}
		SleepForMilliseconds(100);
	}
}
