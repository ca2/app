#pragma once


#include "system_time.h"
#include "result.h"

#include "microsecond_sleep.h"
//namespace datetime
//{
//
//
//   CLASS_DECL_ACME string to_string(::matter * pobject, const ::text::context * pcontext, const ::datetime::result & value);
//
//
//   CLASS_DECL_ACME value span_strtotime(::matter * pobject, const ::text::context * pcontext, const char * psz);
//   CLASS_DECL_ACME value strtotime(::matter * pobject, const ::text::context * pcontext, const char * psz, i32 & iPath, i32 & iPathCount, bool bForceUTC = false);
//
//
//} // namespace datetime


#ifdef WINDOWS


extern "C" CLASS_DECL_ACME time_t timegm(struct tm *tmp);


#endif


extern "C" CLASS_DECL_ACME int c_localtime_offset();


#include "micro_duration.h"


#include "department.h"



