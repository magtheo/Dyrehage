#include <iostream>
#include "servicemanager/service_manager.h"

using namespace ThreadPoolNamespace;
using namespace ServiceNamespace;

// Define services
void databaseService() {
    std::cout << "[DB Service] Checking database for updates...\n";
}

void healthCheckService() {
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
