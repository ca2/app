#pragma once


#ifdef __DEBUG


CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::datetime::time time);
CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::datetime::time_span time);


#endif


//#include "acme/primitive/datetime/secs.h"
//
//
//#include "acme/primitive/datetime/millis.h"
//
//
//#include "acme/primitive/datetime/micros.h"
//
//
//#include "acme/primitive/datetime/nanos.h"
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


CLASS_DECL_ACME void preempt(const ::secs & secs);
CLASS_DECL_ACME void preempt(const ::millis & millis);
CLASS_DECL_ACME void preempt(const ::micros & micros);
CLASS_DECL_ACME void preempt(const ::nanos & nanos);


CLASS_DECL_ACME void precision_wait_seconds(double d);
CLASS_DECL_ACME void precision_wait_milliseconds(double d);
CLASS_DECL_ACME void precision_wait_microseconds(double d);
CLASS_DECL_ACME void precision_wait_nanoseconds(::u64 u);


#include "department.h"



