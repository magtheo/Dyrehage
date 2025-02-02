#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include "../threadpool/threadpool.h"

namespace ServiceNamespace {

class ServiceManager {
public:
    explicit ServiceManager(ThreadPoolNamespace::ThreadPool &pool) : pool(pool) {}

    void addService(std::function<void()> service, int intervalSeconds) {
        services.emplace_back(service, intervalSeconds);
    }

    void start() {
        for (auto& [service, interval] : services) {
            pool.enqueue([service, interval]() {
                while (true) {
                    service();
                    std::this_thread::sleep_for(std::chrono::seconds(interval));
                }
            });
        }
    }

private:
    ThreadPoolNamespace::ThreadPool &pool;
    std::vector<std::pair<std::function<void()>, int>> services;
};

} // namespace ServiceNamespace

#endif // SERVICE_MANAGER_H
