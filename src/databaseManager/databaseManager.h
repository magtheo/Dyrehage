#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <iostream>
#include <sqlite3.h>
#include <mutex>
#include <vector>
#include <string>


namespace Database_n {
class DatabaseManager {
public:
    static DatabaseManager& getInstance() {
        static DatabaseManager instance;
        return instance;
    }

    bool executeQuery(const std::string& query);
    std::vector<std::vector<std::string>> fetchResults(const std::string& query);
    
private:
    DatabaseManager(); // Private constructor
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    sqlite3* db;
    std::mutex dbMutex;
};
}

#endif
