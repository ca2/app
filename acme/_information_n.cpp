// Created by camilo with mummys on 2025-10-21 13:40 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_information_n.h"


item_n40585::item_n40585()
{


}


item_n40585::item_n40585(
   const ::scoped_string& scopedstrName,
   const class ::time& timeGetHere,
   const class ::time& timeLockElapsed,
   const class ::time& timeLookUpElapsed,
   const class ::time& timeLock2Elapsed,
   const class ::time& timeShouldElapsed
) :
   m_strPath(scopedstrName),
   m_timeGetHere(timeGetHere),
   m_timeLockElapsed(timeLockElapsed),
   m_timeLookUpElapsed(timeLookUpElapsed),
   m_timeLock2Elapsed(timeLock2Elapsed),
   m_timeShouldBuildElapsed(timeLock2Elapsed)
{

}


item_n40585::~item_n40585()
{


}


::string item_n40585::as_string() const
{

   ::string str;

   str << m_strPath;

   str.append_format(": {} lk:{} map:{} lk:{} bld:{} cr:{}",
      _017Time(m_timeGetHere),
      _017Time(m_timeLockElapsed),
      _017Time(m_timeLookUpElapsed),
      _017Time(m_timeLock2Elapsed),
      _017Time(m_timeShouldBuildElapsed),
      _017Time(m_timeCreateInstanceElapsed)
      );
   str.append_format("\n        t1:{} ini:{} rcrt:{} ccrt:{} init:{} run:{}",
      _017Time(m_timeT1),
      _017Time(m_timeInitializeElapsed),
      _017Time(m_timeRunCreateElapsed),
      _017Time(m_timeCallCreateElapsed),
      _017Time(m_timeInitElapsed),
      _017Time(m_timeRunElapsed)
   );

   return str;

}


::string information_n40585::as_string() const
{

   ::string str;

   for (auto& item : m_itema)
   {

      str.append(item.as_string());

      str += "\n";

   }

   return str;

}


::string information_n40585::handle_locale_as_string() const
{

   ::string str;

   str.format(": {} + {}\n  locle:{} pd:{} rtini:{} pd:{}", 
      _017Time(m_timeHandleRootHandleLocaleElapsed
         + m_timeHandleRootPadding1Elapsed
         + m_timeHandleRootRootInitElapsed
         + m_timeHandleRootPadding2Elapsed),
      _017Time(m_timeHandleRootDateTimeElapsed
         + m_timeHandleRootMainElapsed
         + m_timeHandleRootSysIncludePathElapsed
         + m_timeHandleRootOnBeforeIncludeElapsed
         + m_timeHandleRootSiteOnBeforeIncludeElapsed
         + m_timeHandleRootSubdomainOnBeforeIncludeElapsed),
      _017Time(m_timeHandleRootHandleLocaleElapsed),
      _017Time(m_timeHandleRootPadding1Elapsed),
      _017Time(m_timeHandleRootRootInitElapsed),
      _017Time(m_timeHandleRootPadding2Elapsed));

   str.append_format("\n    rtini:{}", m_strHandleRootRootInit);

   if (m_timeHandleRootDateTimeElapsed.is_set()
      || m_timeHandleRootMainElapsed.is_set()
      || m_timeHandleRootSysIncludePathElapsed.is_set()
      || m_timeHandleRootOnBeforeIncludeElapsed.is_set()
      || m_timeHandleRootSiteOnBeforeIncludeElapsed.is_set()
      || m_timeHandleRootSubdomainOnBeforeIncludeElapsed.is_set())
   {

      str.append_format("\n  dt:{} mn:{} sys:{} binc:{} site:{} sdmn:{}",
         _017Time(m_timeHandleRootDateTimeElapsed),
         _017Time(m_timeHandleRootMainElapsed),
         _017Time(m_timeHandleRootSysIncludePathElapsed),
         _017Time(m_timeHandleRootOnBeforeIncludeElapsed),
         _017Time(m_timeHandleRootSiteOnBeforeIncludeElapsed),
         _017Time(m_timeHandleRootSubdomainOnBeforeIncludeElapsed));

      str.append_format("\n    site:{}", m_strHandleRootSiteOnBeforeInclude);

   }

   return str;

}




