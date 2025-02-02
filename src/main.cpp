#include <iostream>
#include <thread>
#include <chrono>

void checkDatabase() {
    while (true) {
        std::cout << "Checking database for updates...\n";
        // Simulate database query and processing
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

int main() {
    std::thread worker(checkDatabase);
    worker.detach();  // Let it run in the background

    // Main application loop
    while (true) {
        std::cout << "Main application running...\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
