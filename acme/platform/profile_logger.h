// From ProfileLogger by camilo on 2026-04-25 03:45 <3ThomasBorregaardSørensen!!
#pragma once

//#include <map>
//#include <vector>
//#include "thread/LocalMutex.h"
//#include "util/DateTime.h"


namespace platform
{


   struct processor_times
   {


      ::f64                   m_process;
      ::f64                   m_kernel;
      ::u64                   m_cycle;
      class ::time            m_time;


   };


   // �lass for acquiring processor load metrics.
   class CLASS_DECL_ACME profile_logger :
      virtual public ::particle
   {
   public:

      //private:
      //LocalMutex m_mapMut;
      critical_section m_criticalsection;
      ::map_base < const_char_pointer , ::array_base<processor_times>> m_checkPoints;
      processor_times m_last;
      ::f64 m_dropRate; // time interval in seconds to log statistics
      class ::time m_lastDrop;

      profile_logger();
      ~profile_logger();


      // returns cycles and times deltas from previouse checkpoint
      processor_times checkPoint(const_char_pointer tag);
      ::string_array dropStat();

   };


} // namespace platform


CLASS_DECL_ACME ::platform::profile_logger * profile_logger();


CLASS_DECL_ACME void defer_profile_logger();
