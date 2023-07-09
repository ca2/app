#pragma once


#include "acme/primitive/datetime/file_time.h"
#include "acme/primitive/datetime/system_time.h"


inline file_time as_file_time(const FILETIME & filetime)
{

   return { file_time_t{}, (::u64) ::make_u32(filetime.dwLowDateTime, filetime.dwHighDateTime) };

}



inline FILETIME as_FILETIME(const file_time & filetime)
{

   return {
      .dwLowDateTime =::lower_u32(filetime.m_uFileTime),
      .dwHighDateTime = ::upper_u32(filetime.m_uFileTime)
   };

}


inline system_time as_system_time(const SYSTEMTIME & systemtime)
{

   return {
      systemtime.wYear,
      systemtime.wMonth,
      systemtime.wDayOfWeek,
      systemtime.wDay,
      systemtime.wHour,
      systemtime.wMinute,
      systemtime.wSecond,
      systemtime.wMilliseconds
   };
}



inline SYSTEMTIME as_SYSTEMTIME(const system_time & systemtime)
{

   return {
      .wYear = systemtime.wYear,
      .wMonth = systemtime.wMonth,
      .wDayOfWeek = systemtime.wDayOfWeek,
      .wDay = systemtime.wDay,
      .wHour = systemtime.wHour,
      .wMinute = systemtime.wMinute,
      .wSecond = systemtime.wSecond,
      .wMilliseconds = systemtime.wMilliseconds
   };

}


inline FILETIME as_FILETIME(const SYSTEMTIME & systemtime)
{

   FILETIME filetime;

   ::SystemTimeToFileTime(&systemtime, &filetime);

   return filetime;

}


inline SYSTEMTIME as_SYSTEMTIME(const FILETIME & filetime)
{

   SYSTEMTIME systemtime;

   ::FileTimeToSystemTime(&filetime, &systemtime);

   return systemtime;

}




