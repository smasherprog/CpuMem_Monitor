#include "../cpumem_monitor.h"
#include <assert.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

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
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::thread th([&]() {
        auto counter = 0;
        std::vector<char> mem;
        while (counter++ < 20) {
            auto memusage = mon.getMemoryUsage();
            auto cpuusage = mon.getCPUUsage();
            std::cout << "Total CPU Usage: " << cpuusage.TotalUse << std::endl;
            std::cout << "Total CPU Process Usage: " << cpuusage.ProcessUse << std::endl;
            std::cout << "Physical Process Memory Usage: " << SL::NET::to_PrettyBytes(memusage.PhysicalProcessUsed) << std::endl;
            std::cout << "Total Physical Process Memory Available: " << SL::NET::to_PrettyBytes(memusage.PhysicalTotalAvailable) << std::endl;
            std::cout << "Total Physical Memory Usage: " << SL::NET::to_PrettyBytes(memusage.PhysicalTotalUsed) << std::endl;
            std::cout << "Virtual Process Memory Usage: " << SL::NET::to_PrettyBytes(memusage.VirtualProcessUsed) << std::endl;
            std::cout << "Total Virtual Process Memory Usage: " << SL::NET::to_PrettyBytes(memusage.VirtualTotalAvailable) << std::endl;
            std::cout << "Total Virtual Process Memory Usage: " << SL::NET::to_PrettyBytes(memusage.VirtualTotalUsed) << std::endl;

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
            if (counter == 10) {
                std::cout << "Allocating 20 more MBs" << std::endl;
                mem.reserve(mem.capacity() + static_cast<size_t>(1024 * 1024 * 20));
            }
            if (counter == 11) {
                std::cout << "Allocating 20 more MBs" << std::endl;
                mem.reserve(mem.capacity() + static_cast<size_t>(1024 * 1024 * 20));
            }
            if (counter == 12) {
                std::cout << "Allocating 20 more MBs" << std::endl;
                mem.reserve(mem.capacity() + static_cast<size_t>(1024 * 1024 * 20));
            }
            if (counter == 13) {
                std::cout << "Allocating 20 more MBs" << std::endl;
                mem.reserve(mem.capacity() + static_cast<size_t>(1024 * 1024 * 20));
            }
            if (counter == 14) {
                std::cout << "Deallocating the memory" << std::endl;
                mem.shrink_to_fit();
            }
        }
    });
    th.join();
    runner.join();
    return 0;
}
