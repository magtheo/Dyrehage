#include "database_manager.h"


namespace Database_n{
// Constructor: Open Database
DatabaseManager::DatabaseManager() {
    if (sqlite3_open("zoo_database.db", &db) != SQLITE_OK) {
        std::cerr << "[Database] Failed to open database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "[Database] Opened successfully.\n";
    }
}

// Destructor: Close Database
DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
}

// Execute Queries (Insert, Update, Delete)
bool DatabaseManager::executeQuery(const std::string& query) {
    std::lock_guard<std::mutex> lock(dbMutex);
    char* errMsg = nullptr;

    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "[Database] Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

// Fetch Results (Select Queries)
std::vector<std::vector<std::string>> DatabaseManager::fetchResults(const std::string& query) {
    std::lock_guard<std::mutex> lock(dbMutex);
    sqlite3_stmt* stmt;
    std::vector<std::vector<std::string>> results;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "[Database] Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return results;
    }

    int numCols = sqlite3_column_count(stmt);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int i = 0; i < numCols; i++) {
            const char* val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            row.push_back(val ? val : "NULL");
        }
        results.push_back(row);
    }

    sqlite3_finalize(stmt);
    return results;
}
}