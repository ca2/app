// Created by camilo on 2021-10-05 12:54 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


#include "duration.h"


//template < typename DURATION >
//inline bool integral_duration<DURATION>::operator == (const ::duration & duration) const { return ::duration(*this) == duration; } 
//
//template < typename DURATION >
//inline bool integral_duration<DURATION>::operator < (const ::duration & duration) const { return ::duration(*this) < duration; } 
//
//template < typename DURATION >
//inline bool integral_duration<DURATION>::operator <= (const ::duration & duration) const { return ::duration(*this) <= duration; } 
//
//template < typename DURATION >
//inline bool integral_duration<DURATION>::operator > (const ::duration & duration) const { return ::duration(*this) > duration; } 
//
//template < typename DURATION >
//inline bool integral_duration<DURATION>::operator >= (const ::duration & duration) const { return ::duration(*this) >= duration; } 
//
//template < typename DURATION >
//inline bool integral_duration<DURATION>::operator != (const ::duration & duration) const { return ::duration(*this) != duration; }


//#define COMPARISON_WITH_DURATION(TYPE) \
//inline bool operator == (const TYPE & t, const ::duration & duration) { return ::duration(t) == duration; } \
//inline bool operator < (const TYPE & t, const ::duration & duration) { return ::duration(t) < duration; } \
//inline bool operator <= (const TYPE & t, const ::duration & duration) { return ::duration(t) <= duration; } \
//inline bool operator > (const TYPE & t, const ::duration & duration) { return ::duration(t) > duration; } \
//inline bool operator >= (const TYPE & t, const ::duration & duration) { return ::duration(t) >= duration; } \
//inline bool operator != (const TYPE & t, const ::duration & duration) { return ::duration(t) != duration; } 


DEFINE_COMPARISON_WITH_DURATION(inline, INTEGRAL_NANOSECOND)
DEFINE_COMPARISON_WITH_DURATION(inline, INTEGRAL_MICROSECOND)
DEFINE_COMPARISON_WITH_DURATION(inline, INTEGRAL_MILLISECOND)
DEFINE_COMPARISON_WITH_DURATION(inline, INTEGRAL_SECOND)
DEFINE_COMPARISON_WITH_DURATION(inline, INTEGRAL_MINUTE)
DEFINE_COMPARISON_WITH_DURATION(inline, INTEGRAL_HOUR)
DEFINE_COMPARISON_WITH_DURATION(inline, INTEGRAL_DAY)


//template < typename DURATION >
//inline bool floating_duration<DURATION>::operator == (const ::duration & duration) const { return ::duration(*this) == duration; } 
//
//template < typename DURATION >
//inline bool floating_duration<DURATION>::operator < (const ::duration & duration) const { return ::duration(*this) < duration; } 
//
//template < typename DURATION >
//inline bool floating_duration<DURATION>::operator <= (const ::duration & duration) const { return ::duration(*this) <= duration; }
//
//template < typename DURATION >
//inline bool floating_duration<DURATION>::operator > (const ::duration & duration) const { return ::duration(*this) > duration; }
//
//template < typename DURATION >
//inline bool floating_duration<DURATION>::operator >= (const ::duration & duration) const { return ::duration(*this) >= duration; }
//
//template < typename DURATION >
//inline bool floating_duration<DURATION>::operator != (const ::duration & duration) const { return ::duration(*this) != duration; }


DEFINE_COMPARISON_WITH_DURATION(inline, FLOATING_NANOSECOND)
DEFINE_COMPARISON_WITH_DURATION(inline, FLOATING_MICROSECOND)
DEFINE_COMPARISON_WITH_DURATION(inline, FLOATING_MILLISECOND)
DEFINE_COMPARISON_WITH_DURATION(inline, FLOATING_SECOND)
DEFINE_COMPARISON_WITH_DURATION(inline, FLOATING_MINUTE)
DEFINE_COMPARISON_WITH_DURATION(inline, FLOATING_HOUR)
DEFINE_COMPARISON_WITH_DURATION(inline, FLOATING_DAY)


#include "nanosecond.h"
#include "microsecond.h"
#include "millisecond.h"


#include "second.h"


#include "minute.h"
#include "hour.h"
#include "day.h"



