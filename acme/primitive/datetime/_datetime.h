#pragma once


#ifdef __DEBUG


CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::datetime::time time);
CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::datetime::time_span time);


#endif


//#include "acme/primitive/datetime/second.h"
//
//
//#include "acme/primitive/datetime/::duration.h"
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


CLASS_DECL_ACME void preempt(const ::INTEGRAL_SECOND & second);
CLASS_DECL_ACME void preempt(const ::INTEGRAL_MILLISECOND & millisecond);
CLASS_DECL_ACME void preempt(const ::INTEGRAL_MICROSECOND & microsecond);
CLASS_DECL_ACME void preempt(const ::INTEGRAL_NANOSECOND & nanosecond);


//inline void preempt(const class ::wait & wait) { preempt(integral_millisecond(wait.m_)); }


CLASS_DECL_ACME void precision_wait(const ::integral_nanosecond & second);


#include "department.h"



