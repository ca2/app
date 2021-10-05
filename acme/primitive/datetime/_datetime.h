#pragma once


#ifdef __DEBUG


CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::datetime::time time);
CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::datetime::time_span time);


#endif


//#include "acme/primitive/datetime/second.h"
//
//
//#include "acme/primitive/datetime/millisecond.h"
//
//
//#include "acme/primitive/datetime/microsecond.h"
//
//
//#include "acme/primitive/datetime/nanosecond.h"
//
//
//
//#include "acme/primitive/datetime/duration.h"



class filetime;


#include "acme/primitive/datetime/date_span.h"
#include "acme/primitive/datetime/time_span.h"
#include "acme/primitive/datetime/time.h"
#include "acme/primitive/datetime/zonetime.h"
#include "acme/primitive/datetime/filetime_span.h"
#include "acme/primitive/datetime/filetime.h"




CLASS_DECL_ACME void preempt(const ::duration & duration);


CLASS_DECL_ACME void preempt_second(::i64 iSecond);
CLASS_DECL_ACME void preempt_millisecond(::i64 iMillisecond);
CLASS_DECL_ACME void preempt_microsecond(::i64 iMicrosecond);
CLASS_DECL_ACME void preempt_nanosecond(::i64 iNanosecond);


CLASS_DECL_ACME void precision_wait_seconds(double d);
CLASS_DECL_ACME void precision_wait_milliseconds(double d);
CLASS_DECL_ACME void precision_wait_microseconds(double d);
CLASS_DECL_ACME void precision_wait_nanoseconds(::u64 u);


#include "department.h"



