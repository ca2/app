//
//  windows_time.hpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Soerensen on 14/02/22.
//  14:35
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once



using WORD = ::u16;
using LONG = ::i32;
using WINULONG = ::u32;
using LONGLONG = ::i64;
using ULONGLONG = ::u64;
using NTSTATUS = ::i32;
using DWORD = ::u32;
using LPDWORD = ::DWORD *;


#ifndef _FILETIME_
#define _FILETIME_
typedef struct _FILETIME {
   DWORD dwLowDateTime;
   DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#endif

typedef struct _SYSTEMTIME {
   WORD wYear;
   WORD wMonth;
   WORD wDayOfWeek;
   WORD wDay;
   WORD wHour;
   WORD wMinute;
   WORD wSecond;
   WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;


CLASS_DECL_ACME int_bool FileTimeToSystemTime(const FILETIME * pfiletime, SYSTEMTIME * psystemtime);


CLASS_DECL_ACME int_bool SystemTimeToFileTime(const SYSTEMTIME * psystemtime, FILETIME * pfiletime);


CLASS_DECL_ACME void GetSystemTime(SYSTEMTIME * psystemtime);



