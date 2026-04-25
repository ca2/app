// From ProfileLogger by camilo on 2026-04-25 03:45 <3ThomasBorregaardSørensen!!
#pragma once

//#include <map>
//#include <vector>
//#include "thread/LocalMutex.h"
//#include "util/DateTime.h"


namespace platform
{
   struct ProcessorTimes
   {
      double                  m_process;
      double                  m_kernel;
      unsigned long long      m_cycle;
      class ::time            m_time;
   };

   // �lass for acquiring processor load metrics.
   class CLASS_DECL_ACME ProfileLogger :
      virtual public ::particle
   {
   public:
      ProfileLogger();

      ~ProfileLogger();
      // returns cycles and times deltas from previouse checkpoint
      ProcessorTimes checkPoint(const char *tag);
      ::string_array dropStat();

      //private:
      //LocalMutex m_mapMut;
      critical_section m_criticalsection;
      ::map_base < const char *, ::array_base<ProcessorTimes>> m_checkPoints;
      ProcessorTimes m_last;
      double m_dropRate; // time interval in seconds to log statistics
      class ::time m_lastDrop;
   };


} // namespace platform


CLASS_DECL_ACME ::platform::ProfileLogger & ProfileLogger();



