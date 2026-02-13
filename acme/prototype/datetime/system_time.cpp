//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#include "framework.h"
#include "earth_gregorian_time.h"
#include "system_time.h"
#include "acme/operating_system/time.h"
//#include "acme/prototype/prototype/payload.h"

//namespace acme
//{
//
//
//   void node::system_time_to_earth_time(posix_time * ptime, const system_time & systemtime, int nDST)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//   void node::time_to_system_time(system_time * psystemtime, const posix_time * ptime)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//} // namespace acme

//
//void copy(payload * ppayload, const system_time & systemtime)
//{
//
//   ppayload->set_type(e_type_earth_time, false);
//
//   ppayload->set_type(e_type_time, false);
//
//   ppayload->m_time = systemtime;
//
//}


system_time::system_time(const ::earth::gregorian_time & gregoriantime)
{

   wDayOfWeek = gregoriantime.m_iDayOfWeek;

   wMilliseconds = (unsigned short)(gregoriantime.m_iNanoSecond / 1'000'000);

   wSecond = gregoriantime.m_iSecond;
   wMinute = gregoriantime.m_iMinute;
   wHour = gregoriantime.m_iHour;
   wDay = gregoriantime.m_iDay;
   wMonth = gregoriantime.m_iMonth;
   wYear = gregoriantime.m_iYear;


}


system_time::system_time(now_t)
{


}


system_time::system_time(const ::posix_time & posixtime) :
   system_time(::earth::gregorian_time(posixtime))
{


}

//system_time::system_time(const ::file_time & filetime)
//{
//
//
//}




