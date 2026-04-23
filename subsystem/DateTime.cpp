// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
// //#include "::earth::time.h"
//
// //#include aaa_<crtdbg.h>
//
// ::earth::time::::earth::time()
// : m_timeValue(0)
// {
// }
// ::earth::time::::earth::time(const ::earth::time &dt)
// : m_timeValue(dt.m_timeValue)
// {
// }
//
// ::earth::time::::earth::time(unsigned long long timeValue)
// : m_timeValue(timeValue)
// {
// }
//
// ::earth::time::::earth::time(FILETIME ft)
// {
//   const unsigned long long SECS_BETWEEN_EPOCHS = 11644473600;
//   const unsigned long long SECS_TO_100NS = 10000000;
//
//    // Time since windows epoch in 100ns intervals.
//   unsigned long long winTime100ns = ((unsigned long long)ft.dwHighDateTime << 32) + ft.dwLowDateTime;
//
//    // Time since unix epoch in 100ns intervals.
//   unsigned long long unixTime100ns = winTime100ns - SECS_BETWEEN_EPOCHS * SECS_TO_100NS;
//
//    // Time singe unix epoch in milliseconds.
//   m_timeValue = (unixTime100ns / 10000);
// }
//
// unsigned long long ::earth::time::getTime() const
// {
//   return m_timeValue;
// }
//
// ::earth::time ::earth::time::operator- (const ::earth::time &other)
// {
//   return ::earth::time(getTime() - other.getTime());
// }
//
// ::earth::time ::earth::time::operator+ (const ::earth::time &other)
// {
//   return ::earth::time(getTime() + other.getTime());
// }
//
// void ::earth::time::toFileTime(LPFILETIME ft) const
// {
//   unsigned long long ll;
//   ll = m_timeValue * (10000000 / 1000) + 116444736000000000;
//   ft->dwLowDateTime = (DWORD)ll;
//   ft->dwHighDateTime = ll >> 32;
// }
//
// void ::earth::time::toUtcSystemTime(LPSYSTEMTIME st) const
// {
//   FILETIME ft;
//
//   toFileTime(&ft);
//
//   FileTimeToSystemTime(&ft, st);
// }
//
// void ::earth::time::toLocalSystemTime(LPSYSTEMTIME st) const
// {
//   FILETIME ft, localFt;
//
//   toFileTime(&ft);
//   // Convert file time from UTC format to local.
//   FileTimeToLocalFileTime(&ft, &localFt);
//
//   FileTimeToSystemTime(&localFt, st);
// }
//
// void ::earth::time::toString(::string & target) const
// {
//   SYSTEMTIME systemTime;
//
//   toLocalSystemTime(&systemTime);
//
//   const size_t dateStringMaxLength = 255;
//
//   TCHAR dateString[dateStringMaxLength + 1];
//
//   if (GetDateFormat(LOCALE_USER_DEFAULT,
//         DATE_SHORTDATE,
//         &systemTime,
//         0,
//         dateString,
//         dateStringMaxLength) == 0) {
//     // TODO: Process this error.
//   }
//
//   target-= dateString;
//   target->appendChar(_T(' '));
//
//   const size_t timeStringMaxLength = 255;
//
//   TCHAR timeString[timeStringMaxLength + 1];
//
//   if (GetTimeFormat(
//         LOCALE_USER_DEFAULT,
//         0,
//         &systemTime,
//         0,
//         timeString,
//         timeStringMaxLength) == 0) {
//     // TODO: Process this error.
//   }
//
//   target->appendString(timeString);
// }
//
// ::earth::time ::earth::time::now()
// {
//   SYSTEMTIME st = {0};
//
//   GetLocalTime(&st);
//
//   FILETIME ft;
//
//   SystemTimeToFileTime(&st, &ft);
//
//   ::earth::time dt(ft);
//
//   return dt;
// }
