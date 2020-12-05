#pragma once


#ifndef WINDOWS

typedef struct _SYSTEMTIME {
   ::u16 wYear;
   ::u16 wMonth;
   ::u16 wDayOfWeek;
   ::u16 wDay;
   ::u16 wHour;
   ::u16 wMinute;
   ::u16 wSecond;
   ::u16 wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

void GetSystemTime(LPSYSTEMTIME systime);

#endif


#include "value.h"


//namespace datetime
//{
//
//
//   CLASS_DECL_ACME string to_string(::matter * pobject, const ::acme::str_context * pcontext, const ::datetime::value & value);
//
//
//   CLASS_DECL_ACME value span_strtotime(::matter * pobject, const ::acme::str_context * pcontext, const char * psz);
//   CLASS_DECL_ACME value strtotime(::matter * pobject, const ::acme::str_context * pcontext, const char * psz, i32 & iPath, i32 & iPathCount, bool bForceUTC = false);
//
//
//} // namespace datetime


extern "C" CLASS_DECL_ACME time_t timegm(struct tm *tmp);
extern "C" CLASS_DECL_ACME int c_localtime_offset();


//#include "department.h"



