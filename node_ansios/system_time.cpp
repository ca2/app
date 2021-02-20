//
// Created by camilo on 13/02/2021.
//
#include "framework.h"


//#include <time.h>
//
//
//namespace node_ansios
//{
//
//
//   time_t node::system_time_to_time(const system_time_t &systemtime, i32 nDST)
//   {
//
//
//      if (systemtime.wYear < 1900)
//      {
//
//         __throw(::exception::exception("invalid datetime::time"));
//
//      }
//
//      struct tm tm;
//      tm.tm_sec = systemtime.wSecond;
//      tm.tm_min = systemtime.wMinute;
//      tm.tm_hour = systemtime.wHour;
//
//      tm.tm_wday = systemtime.wDayOfWeek;
//      tm.tm_mday = systemtime.wDay;
//      tm.tm_mon = systemtime.wMonth - 1;
//      tm.tm_year = systemtime.wYear - 1900;
//      tm.tm_isdst = nDST;
//
//      return timegm(&tm);
//
//   }
//
//
//   system_time_t node::time_to_system_time(const ::datetime::time & time)
//   {
//
//      __throw(interface_only_exception());
//
//      return {};
//
//      system_time_t systemtime{};
//
//      struct tm ttm;
//      struct tm * ptm;
//
//      ptm = time.GetGmtTm(&ttm);
//
//      if (!ptm)
//      {
//
//         return systemtime;
//
//      }
//
//      systemtime.wYear = (::u16)(1900 + ptm->tm_year);
//      systemtime.wMonth = (::u16)(1 + ptm->tm_mon);
//      systemtime.wDayOfWeek = (::u16)ptm->tm_wday;
//      systemtime.wDay = (::u16)ptm->tm_mday;
//      systemtime.wHour = (::u16)ptm->tm_hour;
//      systemtime.wMinute = (::u16)ptm->tm_min;
//      systemtime.wSecond = (::u16)ptm->tm_sec;
//      systemtime.wMilliseconds = 0;
//
//      return systemtime;
//
//   }
//
//
//} // namespace node_ansios
//
//
//
