// Created by camilo on 2021-10-05 12:54 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


#include "duration.h"


#define COMPARISON_WITH_DURATION(TYPE) \
inline bool operator == (const TYPE & t, const ::duration & duration) { return ::duration(t) == duration; } \
inline bool operator < (const TYPE & t, const ::duration & duration) { return ::duration(t) < duration; } \
inline bool operator <= (const TYPE & t, const ::duration & duration) { return ::duration(t) <= duration; } \
inline bool operator > (const TYPE & t, const ::duration & duration) { return ::duration(t) > duration; } \
inline bool operator >= (const TYPE & t, const ::duration & duration) { return ::duration(t) >= duration; } \
inline bool operator != (const TYPE & t, const ::duration & duration) { return ::duration(t) != duration; } 


COMPARISON_WITH_DURATION(INTEGRAL_NANOSECOND)
COMPARISON_WITH_DURATION(INTEGRAL_MICROSECOND)
COMPARISON_WITH_DURATION(INTEGRAL_MILLISECOND)
COMPARISON_WITH_DURATION(INTEGRAL_SECOND)
COMPARISON_WITH_DURATION(INTEGRAL_MINUTE)
COMPARISON_WITH_DURATION(INTEGRAL_HOUR)
COMPARISON_WITH_DURATION(INTEGRAL_DAY)


COMPARISON_WITH_DURATION(FLOATING_NANOSECOND)
COMPARISON_WITH_DURATION(FLOATING_MICROSECOND)
COMPARISON_WITH_DURATION(FLOATING_MILLISECOND)
COMPARISON_WITH_DURATION(FLOATING_SECOND)
COMPARISON_WITH_DURATION(FLOATING_MINUTE)
COMPARISON_WITH_DURATION(FLOATING_HOUR)
COMPARISON_WITH_DURATION(FLOATING_DAY)


#include "nanosecond.h"
#include "microsecond.h"
#include "millisecond.h"


#include "second.h"


#include "minute.h"
#include "hour.h"
#include "day.h"



