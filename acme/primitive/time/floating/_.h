// Created by camilo on 2021-10-05 12:55 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once


//#include "acme/primitive/time/floating/time.h"


inline double floating_nanosecond() { return (::f64)::integral_nanosecond(); }

inline double floating_microsecond() { return floating_nanosecond() / 1'000.0; }

inline double floating_millisecond() { return floating_nanosecond() / 1'000'000.0; }

inline double floating_second() { return floating_nanosecond() / 1'000'000'000.0; }

inline double floating_minute() { return floating_nanosecond() / 60'000'000'000.0; }

inline double floating_hour() { return floating_nanosecond() / 3'600'000'000'000.0; }

inline double floating_day() { return floating_nanosecond() / 86'400'000'000'000.0; }



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
//
//
//
