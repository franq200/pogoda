#include "SQLiteEngine.h"
#include "Logger.h"

int ExecQueryCallback(void* data, int argc, char** argv, char** azColName)
{
	SQLiteEngine::Row newRow;
	for (int i = 0; i < argc; i++)
	{
		std::string value = argv[i] ? argv[i] : "NULL";
		newRow.push_back(value);
	}
	static_cast<SQLiteEngine::QueryResult*>(data)->push_back(newRow);
	return 0;
}

SQLiteEngine::~SQLiteEngine()
{
	if (isConnected())
	{
		disconnect();
	}
}

bool SQLiteEngine::connect(const std::string& connectionString)
{
	if (sqlite3_open(connectionString.c_str(), &db_) != SQLITE_OK)
	{
		Logger::GetInstance()->LogError("Cannot open database: " + std::string(sqlite3_errmsg(db_)));
		return false;
	}
	return true;
}

void SQLiteEngine::disconnect()
{
	sqlite3_close(db_);
}

bool SQLiteEngine::isConnected() const
{
	return db_ != nullptr;
}

bool SQLiteEngine::executeQuery(const std::string& query)
{
	char* errMsg = nullptr;
	results_.clear();
	if (sqlite3_exec(db_, query.c_str(), &ExecQueryCallback, static_cast<void*>(&results_), &errMsg) != SQLITE_OK)
	{
		Logger::GetInstance()->LogError("SQL error: " + std::string(errMsg));
		sqlite3_free(errMsg);
		return false;
	}
	return true;
}
