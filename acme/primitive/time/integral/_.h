#pragma once



//#include "acme/primitive/time/time.h"

CLASS_DECL_ACME ::i64 i64_nanosecond();

inline ::i64 i64_microsecond() { return (::i64) (i64_nanosecond() / 1'000); }

inline ::i64 i64_millisecond() { return (::i64) (i64_nanosecond() / 1'000'000); }

inline ::i64 i64_second() { return (::i64) (i64_nanosecond() / 1'000'000'000); }

inline ::i64 i64_minute() { return (::i64) (i64_nanosecond() / 60'000'000'000); }

inline ::i64 i64_hour() { return (::i64) (i64_nanosecond() / 3'600'000'000'000); }

inline ::i64 i64_day() { return (::i64) (i64_nanosecond() / 86'400'000'000'000); }



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










