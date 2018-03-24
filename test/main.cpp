#include "../cpumem_monitor.h"
#include <assert.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;
int gocpugo()
{
    volatile auto count = std::rand();
    if (count < 1000000) {
        count = 1000000;
    }
    volatile auto count1 = 0;
    for (volatile auto i = 0; i < count; i++) {
        count1 += 1;
    }
    return count1;
}
int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));
    SL::NET::CPUMemMonitor mon;
    std::thread runner;

    std::thread th([&]() {
        auto counter = 0;
        while (counter++ < 20) {
            auto memusage = mon.getMemoryUsage();
            auto cpuusage = mon.getCPUUsage();
            std::cout << "Total CPU Usage: " << cpuusage.TotalUse << std::endl;
            std::cout << "Total Process Usage: " << cpuusage.ProcessUse << std::endl;
            std::cout << "Total Physical Process Memory Usage: " << SL::NET::to_PrettyBytes(memusage.PhysicalProcessUsed) << std::endl;
            std::this_thread::sleep_for(1s);
            if (counter == 5) {
                std::cout << "---Starting busy work in this process---" << std::endl;
                runner = std::thread([&]() {
                    auto start = std::chrono::high_resolution_clock::now();
                    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() < 5) {
                        gocpugo();
                    }
                    std::cout << "---Done with busy work in this process---" << std::endl;
                });
            }
        }
    });
    th.join();
    runner.join();
    return 0;
}
