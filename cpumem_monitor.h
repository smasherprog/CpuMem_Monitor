#pragma once

#ifdef WIN32
#include <pdh.h>

#elif __APPLE__

#elif __linux__

#else
#error "Unknown Operating System!"
#endif
namespace SL {
namespace NET {

    class CPUMonitor {
        HANDLE cpuQuery = NULL;
        HANDLE cpuTotal = NULL;
        ULARGE_INTEGER lastCPU = {0};
        ULARGE_INTEGER lastSysCPU = {0};
        ULARGE_INTEGER lastUserCPU = {0};
        int numProcessors = 1;
        HANDLE currentprocess = NULL;

      public:
        CPUMonitor();
        ~CPUMonitor();
        double getTotalUsage();
        double getProcessUsage();
    };

} // namespace NET
} // namespace SL