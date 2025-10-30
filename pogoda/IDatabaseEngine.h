#pragma once
#include <vector>
#include <string>

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
	const QueryResult& getResults() const
	{
		return results_;
	}
protected:
	QueryResult results_;
};

