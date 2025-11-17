#pragma once
#include <string>
#include <vector>
#include <memory>

class IHttpPoller
{
public:
	struct PollResult
	{
	};

public:
	IHttpPoller() = default;
	virtual ~IHttpPoller() = default;
	virtual std::unique_ptr<PollResult> Poll(const std::string& url) = 0;
protected:
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
	{
		size_t totalSize = size * nmemb;
		response->append((char*)contents, totalSize);
		return totalSize;
	}
};

