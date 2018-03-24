# CpuMem_Monitor
<p>Cross platform cpu and memory monitor</p>
<p>Linux/Mac <img src="https://travis-ci.org/smasherprog/CpuMem_Monitor.svg?branch=master" /></p>
<p>Windows <img src="https://ci.appveyor.com/api/projects/status/jb8vc5t4t4f259xa"/><p> 
<h2>No External Dependencies, just a single header file</h2>

```c++
SL::NET::CPUMemMonitor mon;
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
```
