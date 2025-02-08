#include <iostream>
#include "servicemanager/service_manager.h"
#include "threadpool/threadpool.h"
#include "databasemanager/database_manager.h"

using namespace Database_n;
using namespace std;

using namespace ThreadPoolNamespace;
using namespace ServiceNamespace;

void databaseService() {
    DatabaseManager& db = DatabaseManager::getInstance(); // ✅ Correct usage
    db.executeQuery("SELECT * FROM Animals;");
    std::cout << "[DB Service] Checking database for updates...\n";
}

void healthCheckService() {
    DatabaseManager& db = DatabaseManager::getInstance(); // ✅ Any service can access DB
    db.executeQuery("UPDATE Animals SET health_status='Good' WHERE id=1;");
    std::cout << "[Health Service] Checking animal health status...\n";
}

int main() {
    ThreadPool pool(std::thread::hardware_concurrency());
    ServiceManager serviceManager(pool);

    // Register services with their execution intervals
    serviceManager.addService(databaseService, 10);
    serviceManager.addService(healthCheckService, 5);

    // Start all registered services
    serviceManager.start();

    // Keep the main program running
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
