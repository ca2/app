// Created by camilo on 2021-10-05 12:54 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


#include "acme/primitive/time/time.h"


//template < typename DURATION >
//inline bool integral_time<DURATION>::operator == (const class time & time) const { return class ::time(*this) == time; } 
//
//template < typename DURATION >
//inline bool integral_time<DURATION>::operator < (const class time & time) const { return class ::time(*this) < time; } 
//
//template < typename DURATION >
//inline bool integral_time<DURATION>::operator <= (const class time & time) const { return class ::time(*this) <= time; } 
//
//template < typename DURATION >
//inline bool integral_time<DURATION>::operator > (const class time & time) const { return class ::time(*this) > time; } 
//
//template < typename DURATION >
//inline bool integral_time<DURATION>::operator >= (const class time & time) const { return class ::time(*this) >= time; } 
//
//template < typename DURATION >
//inline bool integral_time<DURATION>::operator != (const class time & time) const { return class ::time(*this) != time; }


//#define COMPARISON_WITH_DURATION(TYPE) \
//inline bool operator == (const TYPE & t, const class time & time) { return class ::time(t) == time; } \
//inline bool operator < (const TYPE & t, const class time & time) { return class ::time(t) < time; } \
//inline bool operator <= (const TYPE & t, const class time & time) { return class ::time(t) <= time; } \
//inline bool operator > (const TYPE & t, const class time & time) { return class ::time(t) > time; } \
//inline bool operator >= (const TYPE & t, const class time & time) { return class ::time(t) >= time; } \
//inline bool operator != (const TYPE & t, const class time & time) { return class ::time(t) != time; } 


DEFINE_COMPARISON_WITH_TIME(inline, INTEGRAL_NANOSECOND)
DEFINE_COMPARISON_WITH_TIME(inline, INTEGRAL_MICROSECOND)
DEFINE_COMPARISON_WITH_TIME(inline, INTEGRAL_MILLISECOND)
DEFINE_COMPARISON_WITH_TIME(inline, INTEGRAL_SECOND)
DEFINE_COMPARISON_WITH_TIME(inline, INTEGRAL_MINUTE)
DEFINE_COMPARISON_WITH_TIME(inline, INTEGRAL_HOUR)
DEFINE_COMPARISON_WITH_TIME(inline, INTEGRAL_DAY)


//template < typename DURATION >
//inline bool floating_time<DURATION>::operator == (const class time & time) const { return class ::time(*this) == time; } 
//
//template < typename DURATION >
//inline bool floating_time<DURATION>::operator < (const class time & time) const { return class ::time(*this) < time; } 
//
//template < typename DURATION >
//inline bool floating_time<DURATION>::operator <= (const class time & time) const { return class ::time(*this) <= time; }
//
//template < typename DURATION >
//inline bool floating_time<DURATION>::operator > (const class time & time) const { return class ::time(*this) > time; }
//
//template < typename DURATION >
//inline bool floating_time<DURATION>::operator >= (const class time & time) const { return class ::time(*this) >= time; }
//
//template < typename DURATION >
//inline bool floating_time<DURATION>::operator != (const class time & time) const { return class ::time(*this) != time; }


DEFINE_COMPARISON_WITH_TIME(inline, FLOATING_NANOSECOND)
DEFINE_COMPARISON_WITH_TIME(inline, FLOATING_MICROSECOND)
DEFINE_COMPARISON_WITH_TIME(inline, FLOATING_MILLISECOND)
DEFINE_COMPARISON_WITH_TIME(inline, FLOATING_SECOND)
DEFINE_COMPARISON_WITH_TIME(inline, FLOATING_MINUTE)
DEFINE_COMPARISON_WITH_TIME(inline, FLOATING_HOUR)
DEFINE_COMPARISON_WITH_TIME(inline, FLOATING_DAY)


//#include "nanosecond.h"
//#include "microsecond.h"
//#include "millisecond.h"
//
//
//#include "second.h"
//
//
//#include "minute.h"
//#include "hour.h"
//#include "day.h"



