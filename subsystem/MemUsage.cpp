#include "framework.h"
// //#include "acme/_operating_system.h"
// #include "MemUsage.h"
// //#include "remoting/remoting/win_system/Environment.h"
//
// namespace remoting
// {
//    size_t MemUsage::getCurrentMemUsage()
//    {
//       if (!Environment::isVistaOrLater()) {
//          return 0;
//       }
//       PROCESS_MEMORY_COUNTERS pmc;
//       GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
//       return (size_t)pmc.WorkingSetSize;
//    }
// } // namespace remoting