#pragma once


namespace platform
{

   // Keep this declaration independent of the debug switches and timing headers.
   class CLASS_DECL_ACME console_lifecycle_trace
   {
   public:

      console_lifecycle_trace();
      ~console_lifecycle_trace();

      void system_constructed();
      void system_initialized();
      void start_shutdown();

   private:

      long long m_iPhaseStart;
      bool m_bShuttingDown;

   };

}
