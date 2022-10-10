// Created by camilo on 2021-10-05 12:54 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


#include "duration.h"






//#define COMPARISON_WITH_DURATION(TYPE) \
//inline bool operator == (const TYPE & t, const ::duration & duration) { return ::duration(t) == duration; } \
//inline bool operator < (const TYPE & t, const ::duration & duration) { return ::duration(t) < duration; } \
//inline bool operator <= (const TYPE & t, const ::duration & duration) { return ::duration(t) <= duration; } \
//inline bool operator > (const TYPE & t, const ::duration & duration) { return ::duration(t) > duration; } \
//inline bool operator >= (const TYPE & t, const ::duration & duration) { return ::duration(t) >= duration; } \
//inline bool operator != (const TYPE & t, const ::duration & duration) { return ::duration(t) != duration; } 


DEFINE_COMPARISON_WITH_DURATION(INTEGRAL_NANOSECOND)
DEFINE_COMPARISON_WITH_DURATION(INTEGRAL_MICROSECOND)
DEFINE_COMPARISON_WITH_DURATION(INTEGRAL_MILLISECOND)
DEFINE_COMPARISON_WITH_DURATION(INTEGRAL_SECOND)
DEFINE_COMPARISON_WITH_DURATION(INTEGRAL_MINUTE)
DEFINE_COMPARISON_WITH_DURATION(INTEGRAL_HOUR)
DEFINE_COMPARISON_WITH_DURATION(INTEGRAL_DAY)

DEFINE_COMPARISON_WITH_DURATION(FLOATING_NANOSECOND)
DEFINE_COMPARISON_WITH_DURATION(FLOATING_MICROSECOND)
DEFINE_COMPARISON_WITH_DURATION(FLOATING_MILLISECOND)
DEFINE_COMPARISON_WITH_DURATION(FLOATING_SECOND)
DEFINE_COMPARISON_WITH_DURATION(FLOATING_MINUTE)
DEFINE_COMPARISON_WITH_DURATION(FLOATING_HOUR)
DEFINE_COMPARISON_WITH_DURATION(FLOATING_DAY)


#include "nanosecond.h"
#include "microsecond.h"
#include "millisecond.h"


#include "second.h"


#include "minute.h"
#include "hour.h"
#include "day.h"



