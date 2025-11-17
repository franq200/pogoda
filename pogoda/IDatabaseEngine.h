#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <thread>

class IDatabaseEngine
{
public:
	using Row = std::vector<std::string>;
	using QueryResult = std::vector<Row>;

	virtual ~IDatabaseEngine() = default;
	virtual bool connect(const std::string& connectionString) = 0;
	virtual void disconnect() = 0;
	virtual bool isConnected() const = 0;
	virtual bool executeQuery(const std::string& query) = 0;
	QueryResult getResults(std::thread::id threadId) const
	{
		return results_.at(threadId);
	}
protected:
	std::unordered_map<std::thread::id, QueryResult> results_;
};

