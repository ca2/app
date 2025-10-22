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

   str.append_format(" time:{} lk:{} map:{} lk:{} bld:{} cr:{}",
      _017Time(m_timeGetHere),
      _017Time(m_timeLockElapsed),
      _017Time(m_timeLookUpElapsed),
      _017Time(m_timeLock2Elapsed),
      _017Time(m_timeShouldBuildElapsed),
      _017Time(m_timeCreateInstanceElapsed)
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



