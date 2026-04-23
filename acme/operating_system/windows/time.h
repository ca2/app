// Created by camilo on 2026-04-22 12:43 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/datetime/file_time.h"
#include "acme/prototype/datetime/system_time.h"
#ifdef WINDOWS
#include "acme/_operating_system.h"
#else
#include "acme/operating_system/ansi/windows_time.h"
#endif
#include "acme/operating_system/shared_posix/time1.h"


inline ::file_time as_file_time(const FILETIME &filetime)
{

   return {file_time_t{},
           (unsigned long long)::make_unsigned_long_long(filetime.dwLowDateTime, filetime.dwHighDateTime)};
}


inline FILETIME as_FILETIME(const ::file_time &filetime)
{

   return {.dwLowDateTime = ::lower_unsigned_int(filetime.m_uFileTime),
           .dwHighDateTime = ::upper_unsigned_int(filetime.m_uFileTime)};
}


inline FILETIME as_FILETIME(const SYSTEMTIME &systemtime)
{

   FILETIME filetime;

   ::SystemTimeToFileTime(&systemtime, &filetime);

   return filetime;

}


inline SYSTEMTIME as_SYSTEMTIME(const ::earth::time &time)
{

   SYSTEMTIME st = {};

   struct tm ttm;

   struct tm *ptm;

   ptm = tm_struct(&ttm, time);

   st.wDay = ptm->tm_mday;
   st.wDayOfWeek = ptm->tm_wday;
   st.wHour = ptm->tm_hour;
   st.wMilliseconds = 0;
   st.wMinute = ptm->tm_min;
   st.wMonth = ptm->tm_mon + 1;
   st.wSecond = ptm->tm_sec;
   st.wYear = 1900 + ptm->tm_year;

   return st;
}


inline FILETIME & as_FILETIME(const ::earth::time &time)
{

   FILETIME filetime{};

   auto systemtime = as_SYSTEMTIME(time);

   if (!::SystemTimeToFileTime(&systemtime, &filetime))
   {

#ifdef WINDOWS

      DWORD dwLastError = ::GetLastError();

#endif

      // TRACELASTERROR();

      ::memory_set(&filetime, 0, sizeof(filetime));

   }

   return filetime;

}


inline SYSTEMTIME as_SYSTEMTIME(const FILETIME &filetime)
{

   SYSTEMTIME systemtime;

   ::FileTimeToSystemTime(&filetime, &systemtime);

   return systemtime;
}


inline SYSTEMTIME as_SYSTEMTIME(const system_time &systemtime)
{

   return {.wYear = systemtime.wYear,
           .wMonth = systemtime.wMonth,
           .wDayOfWeek = systemtime.wDayOfWeek,
           .wDay = systemtime.wDay,
           .wHour = systemtime.wHour,
           .wMinute = systemtime.wMinute,
           .wSecond = systemtime.wSecond,
           .wMilliseconds = systemtime.wMilliseconds};
}


inline system_time as_system_time(const SYSTEMTIME &systemtime)
{

   return {systemtime.wYear, systemtime.wMonth,  systemtime.wDayOfWeek, systemtime.wDay,
           systemtime.wHour, systemtime.wMinute, systemtime.wSecond,    systemtime.wMilliseconds};
}



inline void toLocal_SYSTEMTIME(SYSTEMTIME& systemtime)
{

   FILETIME ft, localFt;

   ft = as_FILETIME(systemtime);
   // Convert file time from UTC format to local.
   FileTimeToLocalFileTime(&ft, &localFt);

   FileTimeToSystemTime(&localFt, &systemtime);

}
