#pragma once

#ifndef STARTUP_DELAY_DEBUG
#define STARTUP_DELAY_DEBUG 0
#endif

#if STARTUP_DELAY_DEBUG

#include <chrono>
#include <cstdio>

namespace startup_delay_debug
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
         auto dSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
         std::fprintf(stderr, "Startup phase '%s': %.3f seconds\n", m_pszPhase, dSeconds);
      }
   };

}

#define STARTUP_DELAY_TRACE_SCOPE(name) ::startup_delay_debug::scope startupDelayScope##__LINE__(name)
#define STARTUP_DELAY_TRACE_SCOPE_IF(name, condition) ::startup_delay_debug::scope startupDelayScope##__LINE__(name, (condition))
#define STARTUP_DELAY_TRACE_EVENT(...) do { std::fprintf(stderr, __VA_ARGS__); std::fputc('\n', stderr); } while (false)

#else

#define STARTUP_DELAY_TRACE_SCOPE(name)
#define STARTUP_DELAY_TRACE_SCOPE_IF(name, condition)
#define STARTUP_DELAY_TRACE_EVENT(...)

#endif
