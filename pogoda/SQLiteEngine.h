#pragma once
#include "IDatabaseEngine.h"
#include <sqlite3.h>
#include <mutex>

class SQLiteEngine : public IDatabaseEngine
{
public:
	SQLiteEngine() = default;
	~SQLiteEngine() override;
	bool connect(const std::string& connectionString) override;
	void disconnect() override;
	bool isConnected() const override;
	bool executeQuery(const std::string& query) override;
private:
	std::mutex mutex_;
	sqlite3* db_ = nullptr;
};

