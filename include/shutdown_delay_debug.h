#pragma once

#ifndef SHUTDOWN_DELAY_DEBUG
#define SHUTDOWN_DELAY_DEBUG 0
#endif

#if SHUTDOWN_DELAY_DEBUG

#include <chrono>
#include <cstdio>

namespace shutdown_delay_debug
{

   class scope
   {
   public:
      const char * m_pszPhase;
      std::chrono::steady_clock::time_point m_timeStart;
      bool m_bEnabled;

      explicit scope(const char * pszPhase, bool bEnabled = true) :
         m_pszPhase(pszPhase),
         m_timeStart(std::chrono::steady_clock::now()),
         m_bEnabled(bEnabled)
      {
      }

      ~scope()
      {
         if (!m_bEnabled)
         {
            return;
         }

         auto duration = std::chrono::steady_clock::now() - m_timeStart;
         auto dMilliseconds = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(duration).count();
         // Shutdown tracing must also work after the framework logger is destroyed.
         std::fprintf(stderr, "Shutdown phase '%s': %.3f ms\n", m_pszPhase, dMilliseconds);
      }
   };

}

#define SHUTDOWN_DELAY_TRACE_SCOPE(name) ::shutdown_delay_debug::scope shutdownDelayScope##__LINE__(name)
#define SHUTDOWN_DELAY_TRACE_SCOPE_IF(name, condition) ::shutdown_delay_debug::scope shutdownDelayScope##__LINE__(name, (condition))
#define SHUTDOWN_DELAY_TRACE_EVENT(...) std::fprintf(stderr, __VA_ARGS__)

#else

#define SHUTDOWN_DELAY_TRACE_SCOPE(name)
#define SHUTDOWN_DELAY_TRACE_SCOPE_IF(name, condition)
#define SHUTDOWN_DELAY_TRACE_EVENT(...)

#endif
