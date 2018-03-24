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
        CPUMonitor()
        {
            PdhOpenQuery(NULL, NULL, &cpuQuery);
            // You can also use L"\\Processor(*)\\% Processor Time" and get individual CPU values with PdhGetFormattedCounterArray()
            PdhAddEnglishCounterA(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
            PdhCollectQueryData(cpuQuery);

            SYSTEM_INFO sysInfo;
            FILETIME ftime, fsys, fuser;

            GetSystemInfo(&sysInfo);
            numProcessors = sysInfo.dwNumberOfProcessors;

            GetSystemTimeAsFileTime(&ftime);
            memcpy(&lastCPU, &ftime, sizeof(FILETIME));

            currentprocess = GetCurrentProcess();
            GetProcessTimes(currentprocess, &ftime, &ftime, &fsys, &fuser);
            memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
            memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
        }
        ~CPUMonitor()
        {
            if (cpuQuery == NULL) {
                PdhCloseQuery(cpuQuery);
            }
        }
        double getTotalUsage()
        {
            PDH_FMT_COUNTERVALUE counterVal;
            PdhCollectQueryData(cpuQuery);
            PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
            return counterVal.doubleValue;
        }
        double getProcessUsage()
        {
            FILETIME ftime, fsys, fuser;
            ULARGE_INTEGER now, sys, user;
            double percent = 0.0;
            GetSystemTimeAsFileTime(&ftime);
            memcpy(&now, &ftime, sizeof(FILETIME));
            GetProcessTimes(currentprocess, &ftime, &ftime, &fsys, &fuser);
            memcpy(&sys, &fsys, sizeof(FILETIME));
            memcpy(&user, &fuser, sizeof(FILETIME));
            percent = (sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart);
            percent /= (now.QuadPart - lastCPU.QuadPart);
            percent /= numProcessors;
            lastCPU = now;
            lastUserCPU = user;
            lastSysCPU = sys;
            return percent * 100.0;
        }
    };

} // namespace NET
} // namespace SL