#pragma once



//#include "acme/primitive/time/time.h"

CLASS_DECL_ACME ::i64 integral_nanosecond();

inline ::i64 integral_microsecond() { return (::i64) (integral_nanosecond() / 1'000); }

inline ::i64 integral_millisecond() { return (::i64) (integral_nanosecond() / 1'000'000); }

inline ::i64 integral_second() { return (::i64) (integral_nanosecond() / 1'000'000'000); }

inline ::i64 integral_minute() { return (::i64) (integral_nanosecond() / 60'000'000'000); }

inline ::i64 integral_hour() { return (::i64) (integral_nanosecond() / 3'600'000'000'000); }

inline ::i64 integral_day() { return (::i64) (integral_nanosecond() / 86'400'000'000'000); }



//#include "acme/primitive/time/integral/time.h"


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










