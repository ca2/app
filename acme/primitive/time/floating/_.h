// Created by camilo on 2021-10-05 12:55 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


//#include "acme/primitive/time/floating/time.h"


CLASS_DECL_ACME double floating_nanosecond();

inline double floating_microsecond() { return (::i64)(floating_nanosecond() / 1'000.0); }

inline double floating_millisecond() { return (::i64)(floating_nanosecond() / 1'000'000.0); }

inline double floating_second() { return (::i64)(floating_nanosecond() / 1'000'000'000.0); }

inline ::i64 floating_minute() { return (::i64)(floating_nanosecond() / 60'000'000'000.0); }

inline ::i64 floating_hour() { return (::i64)(floating_nanosecond() / 3'600'000'000'000.0); }

inline ::i64 floating_day() { return (::i64)(floating_nanosecond() / 86'400'000'000'000.0); }



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
